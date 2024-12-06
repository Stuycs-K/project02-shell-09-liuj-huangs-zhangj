#ifndef REDIRECT_H
#define REDIRECT_H
void stdoutRedirExec(char* path, char* args[]);
void stdinRedirExec(char* path, char* args[]);
int redir(char* args[], int argsLen);
#endif
