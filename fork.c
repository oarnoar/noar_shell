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

int main(int argc, char *argv[], char *envp[]) 
{
    pid_t pid = fork();
    int stc;

    if (pid == 0)
    { // Child process   
    
        printf("[K] My PID: %d\n", getpid());
    
        execv(argv[1], &argv[1]);
    
        exit(1); // only when error case 
    }

    if (pid > 0) 
    { // Parent process

        printf("[E] My PID: %d\n", getpid());

        printf("[E] PID Child process: %d\n", pid);

        wait(&stc); // Wait for the child

        if (WIFEXITED(stc)) 
        {

            printf("[E] Child process ended with %d\n",

                WEXITSTATUS(stc));

        }
}
}