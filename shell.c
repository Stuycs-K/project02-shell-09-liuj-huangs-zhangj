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
