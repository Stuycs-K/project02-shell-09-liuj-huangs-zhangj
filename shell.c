#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void parse_args(char* line, char** arg_ary){
  int counter = 0;
  while((arg_ary[counter] = strsep(&line, " "))){
    counter++;
  }
}
int main(){
  char buffer[256];
  fgets(buffer, 255, stdin);
  char** args;
  char* line;
  strcpy(line, buffer);
  parse_args(line, args);
  printf("%s\n", args);
  execvp(args[0], args);
  return 0;
}
