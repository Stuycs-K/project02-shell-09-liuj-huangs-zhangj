#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "execute.h"
#include "input.h"
#include "path.h"

int main(){ // Main function, runs forever until exit or ctrl+D, takes no args and returns 0 if it exits normally and 1 if it exits through an error
  while (1){
    // Print shell prompt
    printPath();
    // Taking input
    char *input;
    input = takeInput();
    // Executing command
    execute(input);
  }
  return 0;
}

// chdir(): Change Current Directory
// getcwd(): Get Current Directory
