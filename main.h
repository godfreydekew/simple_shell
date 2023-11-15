#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>   
#include <termios.h>   
int runfork(void);
void executeCommand(char **arguments);
void freeArguments(char **arguments);
char **my_strtok(char my_args[], char delim);
int contains_only_spaces(const char *str);
int my_setenv_unset( char **arguments);
void my_exit(char **argss);
void trimNewline(char *str);
int checkAndExecute(char **arguments);

#define MAX_INPUT_SIZE 1024
#endif  
