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



int main(int argc, char *argv[], char *env[])
{
	int status;
	char filepath[256];
while(1){
	/*if(argv[1])
	{
		strcpy(filepath, argv[1]);
	}*/
	/*
	else 
	{
	i	printf("#cisfun$ ");
		scanf("%s", filepath);
	}*/
	printf("#cisfun$ ");
	if( fgets(filepath, sizeof(filepath), stdin)== NULL)
	{
		exit(1);
	}

	char *delim = " ";

	size_t len = strlen(filepath);
	 if (len == 1)
        {
                continue;
        }
        if (len > 0 && filepath[len - 1] == '\n') {
            filepath[len - 1] = '\0';
        }
	
	if (len == 1)
	{
		continue;
	}
	int i = 0;
	char *token;
	char *arguments[256];
	token = strtok(filepath, delim);

	while(token != NULL)
	{
		arguments[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}

	arguments[i] = NULL;
	i = 0;
	printf("%s \n", arguments[i]);

	  if (strcmp(arguments[i], "exit") == 0)
	  	{
			int temp = atoi(arguments[1]);

	
			while(arguments[i])
			{
				free(arguments[i]);
				i++;
			}

        		exit(temp);
	    	}
	struct stat st;
		/*const char *prog = arguments[i];
		if(system("command -v prog > /dev/null 2>&1") ==0)
		{
			printf("exist\n");
		}
		else
		{
			return 0;
		}*/

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
	/*
	if (WIFEXITED(status))
	{
		if(WEXITSTATUS(status))
		{
			printf("\n%s No such file or directory", argv[0]);
		}
	}*/
	int x = 0;
	while (arguments[x])
	{
		free(arguments[x]);
		x++;
	}


}

	return 0;
}



