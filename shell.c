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

void execute(char* string){
  char* function;
  while((function = strsep(&string, ";"))){ // splitting into multiple functions
    char* args[100];
    parse_args(function, args);
    pid_t child; // making child to sacrifice to function
    child = fork();
    if(child<0){ // error handling
      perror("fork fail");
      exit(1);
    }
    if(child == 0){
      int exec;
      exec = execvp(args[0], args); // child running function
      if(exec<0){ // error handling
        perror("fork fail");
        exit(1);
      }
    }
    else{
      wait(NULL); // awaiting child death
    }
  }
}

char *takeInput(){
  char buffer[256];
  fgets(buffer, 255, stdin);
  char* copy = (char *) malloc(256);
  sscanf(buffer, "%[^\n]", copy);
  return copy;
}

int main(){
  char cwd[256];
  getcwd(cwd, sizeof(cwd));
  printf("%s $", cwd);
  // taking input
  char *input;
  input = takeInput();
  // executing method
  execute(input);
  return 0;
}

// chdir(): Change Current Directory
// getcwd(): Get Current Directory
