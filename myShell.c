#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifdef _WIN32
#include <process.h>
typedef int pid_t;
#define getpid _getpid
#define execv _execv
#define wait(x) _wait(x)
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

void get_args(char **args, char *scanline)
{
    int len = strlen(scanline);
    args[0] = scanline;
    size_t j = 1;
    for (size_t i = 0; i < len; i++)
    {
        if (scanline[i] == ' ')
        {
            scanline[i] = '\0';
            args[j] = &(scanline[i + 1]);
            j++;
        }
    }
    args[j] = NULL;
}
int main(int argc, char *argv[], char *envp[])
{
    int pid;
    char *scanline;
    char *mypath;
    char *myprompt;
    char *args[256];
    char path[256];
    char input[4096];

    mypath = getenv("MYPATH");
    if (mypath == NULL)
    {
        mypath = "/bin";
    }

    myprompt = getenv("MYPROMPT");
    if (myprompt == NULL)
    {
        myprompt = "> ";
    }
    do
    {
        printf("%s", myprompt);
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("exit\n");
            exit(0);
        }
        input[strcspn(input, "\n")] = '\0';
        scanline = input;
        get_args(args, scanline);
        if (strcmp(args[0], "exit") == 0)
        {
            exit(0);
        }
        pid = fork();
        if (pid == 0)
        {
            sprintf(path, "%s/%s", mypath, args[0]);
            printf("I am the Child process, start: %s\n", path);
            execv(path, args);
            exit(-1);
        }
        if (pid > 0)
        {
            printf("I am the Parent process, the Child is %d.\n",pid);
            wait(NULL);
        }
    } while (1);
}