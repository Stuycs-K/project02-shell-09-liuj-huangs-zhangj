#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "redirect.h"

int parse_args( char * line, char ** arg_ary ){
  int counter = 0;
  while((arg_ary[counter] = strsep(&line, " "))){
    counter++;
  }
  return counter;
}

void cd(char* path){
  chdir(path);
}

void execute(char* string){
  char* function;
  int argsLen;
  int redired;
  while((function = strsep(&string, ";"))){ // splitting into multiple functions
    char* args[100];
    argsLen = parse_args(function, args);
    if(strcmp(args[0], "exit") == 0){ // exit command 
      exit(0);
    }
    if (strcmp(args[0], "cd") == 0){ //cd command 
      if (args[1] == NULL || strcmp(args[1], "~") == 0){
        cd(getenv("HOME"));
      }
      else{
        cd(args[1]); 
      }
    }
    else{
      pid_t child; // making child to sacrifice to executing command
      child = fork();
      if(child<0){ // error handling
        perror("fork fail");
        exit(1);
      }
      if(child == 0){ // Child executes command
        redired = redir(args, argsLen);
        if (redired == 0){ // Check if a redirect command was already executed
          if(strcmp(args[0], "") != 0 || strlen(args[1]) > 0){
            int exec;
            exec = execvp(args[0], args); // Execute command
            if(exec<0){ // error handling
              perror("execvp fail");
              exit(1);
            }
          }
        }
      }
      else{
        wait(NULL); // parent awaits child death
      }
    }
  }
}
