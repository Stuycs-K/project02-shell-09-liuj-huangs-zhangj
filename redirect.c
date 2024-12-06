#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

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
