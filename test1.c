#include"main.h"


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
char **my_strtok(char my_args[])
{
    int i = 0, x = 0, j = 0;
    char my_string[256];
    char delim = ' ';
    printf("welcome\n");

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
    printf("bye\n");
    return tokenized_strings;
}

int contains_only_spaces(const char *str)
 {
    while (*str) 
    {
        if (*str != ' ') 
        {
            return 0; // Not a space, string doesn't contain only spaces
        }
        str++;
    }
    return 1; // String contains only spaces
}



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
                         return 0;   
                }
                else if ( strcmp(arguments[0], "unsetenv") == 0 &&arguments[1] != NULL && arguments[2] == NULL)
                {
                        if(unsetenv(arguments[1]) != 0)
                        {
                                perror("unsetenv");
                                exit(EXIT_FAILURE);
                        }
                         return 0;      
                }
                else
                {
                        fprintf(stderr ,"Wrong arguments for %s\n", arguments[0]);
                         return 0;   
                }
             
            }
             return 1;  
}

int main(int argc, char *argv[], char *env[])
{
        int status, i, x = 0, y = 0;
        char filepath[256];

        while(1)
        {
            printf("#cisfun$ ");
            if( fgets(filepath, sizeof(filepath), stdin)== NULL)
            {
                    exit(1);
            }

            

            size_t len = strlen(filepath);
           
            if (len > 0 && filepath[len - 1] == '\n')
            {
                filepath[len - 1] = '\0';
            }

            if (contains_only_spaces(filepath))
            {
                continue;
            }

            char **arguments = my_strtok(filepath);
            i = 0;
             if (strcmp(arguments[i], "exit") == 0)
                {
                    int temp;
                    if (arguments[1] == NULL)
                    {
                        temp=0;
                    }
                    else
                    {
                    temp = atoi(arguments[1]);
                    }
                    while (arguments[i])
                    {
                        free(arguments[i]);
                        i++;
                    }
                    free(arguments);
                    exit(temp);
                }
                else if (my_setenv_unset(arguments) == 0)
                {
                     while (arguments[i])
                    {
                        free(arguments[i]);
                        i++;
                    }
                    free(arguments);
                    continue;
                }
                    
            
            struct stat st;

            char bin_folder[100] = "/bin/";
            char usr_folder[100] = "/usr/bin/";
            strcat(bin_folder, arguments[i]);
            strcat(usr_folder, arguments[i]);

            if (stat(arguments[i], &st) == 0 || stat(bin_folder, &st) == 0 || stat(usr_folder, &st) == 0  )
            {
                printf(" FOUND\n");
            }
            else
            {
                fprintf(stderr, "File not  FOUND\n");
                    continue;
            }

            

            int pid = runfork();

            if (pid == 0)
            {
                    execvp(arguments[0], arguments);
                    perror("./shell");
                    return 5;
            }
            wait(&status);
                   
            while (arguments[x])
            {
                    free(arguments[x]);
                    x++;
            }
            free(arguments);
            x = 0;
          
           /* while (tokenized_strings[y])
            {
                free(tokenized_strings[y]);
                x++;
            }
            free(tokenized_strings);*/



    }

        return 0;
}

