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

void redirStdout(char* path){
  int fd1 = open(path, O_WRONLY);
  dup(1);
  dup2(1, fd1);
}

void execute(char* string){
  char* function;
  int argsLen;
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
      char* cmd;
      for (int i = 0; i<argsLen; i++){
        strcat(cmd, args[i]);
        if (args[i] == '>'){
          char* path;
          path = args[i+1];
          redirStdout(path);
        }
      }
      int exec;
      exec = execvp(args[0], args); // child running function
      if(exec<0){ // error handling
        perror("fork fail");
        exit(1);
      }
      if (strcmp(args[0], "cd") == 0){
        cd(args[1]);
      }
      else{
        int exec;
        exec = execvp(args[0], args); // child running function
        if(exec<0){ // error handling
          perror("fork fail");
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
