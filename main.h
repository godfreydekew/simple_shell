#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>   // Standard I/O functions
#include <stdlib.h>  // Standard library functions
#include <string.h>  // String manipulation functions
#include <unistd.h>  // POSIX operating system API
#include <sys/types.h>  // Data types used in system calls
#include <sys/wait.h>   // Process management
#include <sys/stat.h>   // File status and permissions
#include <fcntl.h>   // File control options
#include <signal.h>   // Signal handling
#include <errno.h>   // Error handling
#include <dirent.h>   // Directory manipulation
#include <pwd.h>   // Password and group database access
#include <grp.h>   // Group database access
#include <time.h>   // Date and time functions
#include <termios.h>   // Terminal I/O
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
