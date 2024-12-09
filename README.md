[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

**1. Group Members:** Jason Liu, Stanley Huang, Julien Zhang

**2. Creative Group Name:** Put Something In I Don't Know

**3. Successful Features:** 
- Prompting user for input and reading from stdin
- Parsing the argument
- Forking and having the child execvp the command
- Supporting use of semicolons to type multiple commands in one line
- Getting cd to work properly
- Printing the path before the prompt
- Shortening the path to replace the home directory with ~
- Quitting the shell using the exit command or by pressing ctrl + D
- Commands with 1 redirection operator (either > or <)
- Commands with 1 pipe (|) using a temp file
- Taking commands from a text file and running them (./shell < lines.txt)

**4. Attempted Unsuccessful Features:**

**5. Known Bugs:**

**6. Other Comments:**

**7. Function Headers:**
shell.c:
int main();

input.c:
char *takeInput();

path.c:
void printPath();

execute.c:
void parse_args( char * line, char ** arg_ary );
void cd(char* path);
void execute(char* string);

redirect.c:
void stdoutRedirExec(char* path, char* args[]);
void stdinRedirExec(char* path, char* args[]);
void PipeRedirExec(char* args[], int pipeLocation, int argsLen);
int redir(char* args[], int argsLen);
