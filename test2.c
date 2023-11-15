#include"main.h"

/**
 * runfork - Create a new process using fork
 *
 * Return: The process ID (pid) of the child process if successful,
 *         otherwise, exit with an error message.
 */
int runfork(void)
{
        int pid = fork();
        if (pid < 0)
        {

                perror("Fork");
                exit(1);
        }
        return (pid);
}

/**
 * my_strtok - Tokenize a string based on a delimiter
 *
 * @my_args: The input string to be tokenized
 * @delim: The delimiter used for tokenization
 *
 * Return: An array of strings representing the tokens.
 *         NULL if the input string is empty.
 */
char **my_strtok(char my_args[], char delim)
{
        int i = 0, x = 0, j = 0;
        char my_string[256];

        char **tokenized_strings = malloc(1024 * sizeof(char*));

        while (my_args[i])
        {
               if (my_args[i] == '\0')
                       return NULL;
               else if (my_args[i] == delim)
               {
                       i++;
                       continue;
               }
               else
               {
                        while (my_args[i] != '\0' && my_args[i] != delim)
                        {
                                my_string[x++] = my_args[i++];
                        }
               my_string[x] = '\0';
               tokenized_strings[j++] = strdup(my_string);
               x = 0;
               }
         }
         tokenized_strings[j] = NULL;
         return (tokenized_strings);
}

/**
 * contains_only_spaces - Check if a string contains only spaces and newlines
 *
 * @str: The input string to be checked
 *
 * Return: 1 if the string contains only spaces and newlines, 0 otherwise.
 */
int contains_only_spaces(const char *str)
{
        while (*str)
        {
       	        if (*str != ' ' && *str != '\n')
                {
                        return(0);
                }
        str++;
        }
        return(1);
}

/**
 * my_setenv_unset - Set or unset environment variables based on input arguments
 *
 * @arguments: An array of strings containing the command and its arguments
 *
 * Return: 0 on success, 1 on failure
 */

int my_setenv_unset( char **arguments)
{
            if (strcmp(arguments[0], "setenv") == 0 || strcmp(arguments[0], "unsetenv") == 0 )
            {
		     if( strcmp(arguments[0], "setenv") == 0 && arguments[1] != NULL && arguments[2] != NULL && arguments[3] == NULL)
		     {
			     if((setenv(arguments[1], arguments[2], 1)) != 0)
                       	     {
				     perror("setenv");
                                     exit(EXIT_FAILURE);
                             }
                             return (0);
                     }
		     
                     else if ( strcmp(arguments[0], "unsetenv") == 0 &&arguments[1] != NULL && arguments[2] == NULL)
                     {
                             if(unsetenv(arguments[1]) != 0)
                       	     {
				     
                               	     perror("unsetenv");
                                     exit(EXIT_FAILURE);
                             }
                             return(0);
                     }
                     else
                     {
			     
                             fprintf(stderr ,"Wrong arguments for %s\n", arguments[0]);
                             return (0);
                     }

            }

            return (1);
}

/**
 * my_exit - Exit the shell with a specified status or 0 if no status provided
 *
 * @argss: An array of strings containing the command and its arguments
 */

void my_exit(char **argss)
{
        int i = 0;
        if ( strcmp(argss[i], "exit") == 0 )
        {
                int temp;
                if (argss[1] == NULL)
                {
                        temp=0;
                }
                else
                {
                        temp = atoi(argss[1]);
                }
                while (argss[i])
                {
                        free(argss[i]);
                        i++;
                }
                free(argss);
                exit(temp);
	}
}

/**
 * trimNewline - Trim newline character from the end of a string
 *
 * @str: The string to be trimmed
 */
void trimNewline(char *str)
{
	 size_t len = strlen(str);
   	 if (len > 0 && str[len - 1] == '\n')
   	 {
        	str[len - 1] = '\0';
   	 }
	 else
	 {
        	return;
   	 }
}

/**
 * checkAndExecute - Check if the command in arguments is executable and execute it
 *
 * @arguments: Array of strings representing the command and its arguments
 *
 * Return: 1 if the command is executable and executed successfully, 0 otherwise
 */
int checkAndExecute(char **arguments)
{
   	 struct stat st;
   	 char bin_folder[100] = "/bin/";
   	 char usr_folder[100] = "/usr/bin/";
   	 strcat(bin_folder, arguments[0]);
   	 strcat(usr_folder, arguments[0]);

   	 if (stat(arguments[0], &st) == 0 || stat(bin_folder, &st) == 0 || stat(usr_folder, &st) == 0) 
	 {
       	         executeCommand(arguments);
       	         return (1);
         }
	 else 
	 {
                 fprintf(stderr, "Bash: Command not FOUND\n");
                 return (0);
         }
}

/**
 * executeCommand - Execute the given command with its arguments in a child process
 *
 * @arguments: Array of strings representing the command and its arguments
 */
void executeCommand(char **arguments)
{
   	 int status;
   	 int pid = runfork();

   	 if (pid == 0)
	 {
       		 if (execvp(arguments[0], arguments) == -1)
		 {
           		 perror("execvp");
           		 exit(EXIT_FAILURE);
       		 }
   	 }
	 else if (pid < 0)
	 {
       		 perror("Fork");
       		 exit(EXIT_FAILURE);
   	 }
	 else
	 {
       		 waitpid(pid, &status, 0);
   	 }
   	 freeArguments(arguments);
}

/**
 * executeCommand - Execute the given command with its arguments in a child process
 *
 * @arguments: Array of strings representing the command and its arguments
 */

void freeArguments(char **arguments)
{
   	 int i = 0;
   	 while (arguments[i])
	 {
       		 free(arguments[i]);
       		 i++;
   	 }
   	 free(arguments);
}

/**
 * main - Entry point for the simple shell program
 *
 * @argc: Number of arguments passed to the program
 * @argv: Array of strings containing the command-line arguments
 * @env: Array of strings containing the environment variables
 *
 * Return: 0 on successful completion
 */

int main(void)
{
   	 char **arguments, filepath[256];	

   	 while (1)
    	 {
	  	 write(STDOUT_FILENO, "#cisfun$ ", 9);
       		 if (fgets(filepath, sizeof(filepath), stdin) == NULL)
		 {
           		 exit(1);
		 }

	         trimNewline(filepath);

       		 if (contains_only_spaces(filepath))
       		 {
           		 continue;
       		 }

       		 arguments = my_strtok(filepath, ' ');
       		 my_exit(arguments);

 		 if (my_setenv_unset(arguments) == 0 || !checkAndExecute(arguments))
  		 {
           		 continue;
       		 }
   	 }

   	 return (0);
}
