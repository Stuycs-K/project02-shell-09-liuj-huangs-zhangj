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

**4. Attempted Unsuccessful Features:**

**5. Known Bugs:**

**6. Other Comments:**

**7. Function Headers:**
Shell.c:
int main();

Input.c:
char *takeInput();

Path.c:
void printPath();

Execute.c:
void parse_args( char * line, char ** arg_ary );
void cd(char* path);
void execute(char* string);
