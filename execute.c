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
    if(strcmp(args[0], "exit") == 0){ // exit command exit
      exit(0);
    }
    pid_t child; // making child to sacrifice to function
    child = fork();
    if(child<0){ // error handling
      perror("fork fail");
      exit(1);
    }
    if(child == 0){
      redired = redir(args, argsLen);
      if (redired == 1){
        printf("hi\n");
      }
      else if (strcmp(args[0], "cd") == 0){
        cd(args[1]);
      }
      else if(strcmp(args[0], "") != 0 || strlen(args[1]) > 0){
        int exec;
        exec = execvp(args[0], args); // child running function
        if(exec<0){ // error handling
          perror("execvp fail");
          exit(1);
        }
      }
    }
    else{
      wait(NULL); // awaiting child death
    }
  }
}
