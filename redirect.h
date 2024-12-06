#ifndef REDIRECT_H
#define REDIRECT_H
int redir(char* args[], int argsLen);
void stdoutRedirExec(char* path, char* args[]);
void stdinRedirExec(char* path, char* args[]);
#endif
