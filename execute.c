#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void parse_args( char * line, char ** arg_ary ){
  int counter = 0;
  while((arg_ary[counter] = strsep(&line, " "))){
    counter++;
  }
}

void cd(char* path){
  chdir(path);
}

void execute(char* string){
  char* function;
  int argsLen;
  int stdoutRedir = 0;
  int stdinRedir = 0;
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
      char* path;
      stdoutRedir = 0;
      stdinRedir = 0;
      for (int i = 0; i<argsLen; i++){
        if (strcmp(args[i], ">") == 0){
          path = args[i+1];
          stdoutRedir = 1;
          args[i] = NULL;
          break;
        }
        if (strcmp(args[i], "<") == 0){
          path = args[i+1];
          stdinRedir = 1;
          args[i] = NULL;
          break;
        }
      }
      if (stdoutRedir == 1){
        remove(path);
        int fd1 = open(path, O_WRONLY | O_APPEND | O_CREAT, 0600);
        dup(1);
        dup2(fd1, 1);
        int exec;
        close(fd1);
        exec = execvp(args[0], args);
        if (exec<0){
          perror("stoutRedirect fail");
          exit(1);
        }
      }
      else if (stdinRedir == 1){
        int fd1 = open(path, O_RDONLY);
        dup(0);
        dup2(fd1, 0);
        int exec;
        close(fd1);
        exec = execvp(args[0], args);
        if (exec<0){
          perror("stdinRedirect fail");
          exit(1);
        }
      }
      else if (strcmp(args[0], "cd") == 0){
        cd(args[1]);
      }
      else{
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