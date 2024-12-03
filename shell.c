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

void printPath(){
  char currCwd[256];
  char homeCwd[256];
  getcwd(currCwd, sizeof(currCwd));
  chdir(getenv("HOME"));
  getcwd(homeCwd, sizeof(homeCwd));
  chdir(currCwd);
  if (strlen(currCwd) < strlen(homeCwd)){
    printf("%s $", currCwd);
  }
  else{
    char* shortCwd = "~/";
    char* temp = strstr(currCwd, homeCwd); 
    strcat(shortCwd, temp);
    printf("%s $", shortCwd);
  }
}

void cd(char* path){
  chdir(path);
}

int main(){
  while (1){
    char buffer[256];
    printPath();
    fgets(buffer, 255, stdin);
    char* copy = (char *) malloc(256);
    sscanf(buffer, "%[^\n]", copy);
    char* function;
    while((function = strsep(&copy, ";"))){ // splitting into multiple functions
      char* args[100];
      parse_args(function, args);
      pid_t child; // making child to sacrifice to function
      child = fork();
      if(child<0){ // error handling
          perror("fork fail1");
          exit(1);
      }
      if(child == 0){
        if (strcmp(args[0], "cd") == 0){
          chdir(args[1]);
        }
        else{
          int exec;
          exec = execvp(args[0], args); // child running function
          if(exec<0){ // error handling
            perror("fork fail2");
            exit(1);
          }
        }
      }
      else{
        wait(NULL); // awaiting child death
      }
    }
    free(copy);
    free(function);
  }
  return 0;
}
