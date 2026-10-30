#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#define getpid _getpid
#define execv _execv
#else
#include <unistd.h>
#endif

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("PID: %d\n", getpid());
    intptr_t exec_status;
    
#ifdef _WIN32
    const char **exec_argv = malloc((size_t)argc * sizeof(*exec_argv));
    if (exec_argv == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        exec_argv[i - 1] = argv[i];
    }
    exec_argv[argc - 1] = NULL;
    exec_status = execv(argv[1], exec_argv);
    free(exec_argv);
#else
    exec_status = execv(argv[1], &argv[1]);
#endif

    if (exec_status == -1) {
        perror("execv");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}