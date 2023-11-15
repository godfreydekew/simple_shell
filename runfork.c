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
