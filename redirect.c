#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "execute.h"

void stdoutRedirExec(char* path, char* args[]){
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

void stdinRedirExec(char* path, char* args[]){
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

int redir(char* args[], int argsLen){
  char* path;
  int stdoutRedir = 0;
  int stdinRedir = 0;
  for (int i = 0; i<argsLen; i++){
    if (strcmp(args[i], "|") == 0){
       MetalPipe = 1;
       args[i] = NULL;
       pipelocation = i;
       break;
   }
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
    stdoutRedirExec(path, args);
    return 1;
  }
  else if (stdinRedir == 1){
    stdinRedirExec(path, args);
    return 1;
  }
  return 0;
}

int pipe(char* args[]){
  pid_t bb;
  bb = fork();
  if(bb < 0){
      perror("fork fail");
      exit(1);
  }
  if(bb == 0){
      char * arg1 = malloc(sizeof(args));
      strcpy(arg1, args[0]);
      for(int i = 1; i < pipelocation; i++){
          strcat(arg1, args[i]);
      }
      strcat(arg1, " > temp.txt");
      execute(arg1);
      return 0;
  }
  else{
      wait(NULL);
      char * arg2 = malloc(sizeof(args));
      strcpy(args2, args[pipelocation+1]);
      for(int i = pipelocation + 2; i < argslen; i++){
          strcat(arg2, arg[i]);
      }
      strcat(arg2, " < temp.txt");
      execute(arg2);
      remove("temp.txt");
  }
}
