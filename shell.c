#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int parse_args( char * line, char ** arg_ary ){
  int counter = 0;
  while((arg_ary[counter] = strsep(&line, " "))){
    counter++;
  }
  return counter;
}

void printPath(){
  char currCwd[256];
  char homeCwd[256];
  getcwd(currCwd, sizeof(currCwd));
  chdir(getenv("HOME"));
  getcwd(homeCwd, sizeof(homeCwd));
  chdir(currCwd);
  if (strlen(currCwd) < strlen(homeCwd)){
    printf("%s $ ", currCwd);
    fflush(stdout);
  }
  else{
    char shortCwd[256];
    char* temp = strstr(currCwd, homeCwd);
    strcpy(shortCwd, "");
    strcat(shortCwd, "~");
    strcat(shortCwd, temp);
    printf("%s $ ", shortCwd);
    fflush(stdout);
  }
}

void cd(char* path){
  chdir(path);
}

void execute(char* string){
  char* function;
  int argsLen;
  int redir = 0;
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
      char* args2[100];
      char* path;
      redir = 0;
      for (int i = 0; i<argsLen; i++){
         if (strcmp(args[i], ">") == 0){
          path = args[i+1];
          redir = 1;
          args2[i] = NULL;
          break;
        }
	      strcpy(args2[i],args[i]);
      }
      if (redir == 1){
        int fd1 = open(path, O_WRONLY | O_APPEND | O_CREAT, 0600);
        dup(1);
        dup2(fd1, 1);
        int exec;
        exec = execvp(args2[0], args2);
        close(fd1);
        if (exec<0){
          perror("redirect stdout fail");
          exit(1);
        }
      }
      if (strcmp(args[0], "cd") == 0){
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

char *takeInput(){
  char buffer[256];
  char *check;
  check = fgets(buffer, 255, stdin);
  if(check == NULL){ // Ctrl-D exit
    exit(0);
  }
  char* copy = (char *) malloc(256);
  sscanf(buffer, "%[^\n]", copy);
  return copy;
}

int main(){
  while (1){
    printPath();
    // taking input
    char *input;
    input = takeInput();
    // executing method
    execute(input);
  }
  return 0;
}

// chdir(): Change Current Directory
// getcwd(): Get Current Directory
