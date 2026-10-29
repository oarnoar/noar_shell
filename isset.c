#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
isset checks if a given environment variable has been set
*/

int main(int argc, char *argv[], char *envp[]) 
{
    if (argc < 2)
    return 1;

    int verbose = 0;
    
    if (argc > 2)
        if (strcmp(argv[1], "-v") == 0)
            verbose = 1;
        char *key = argv[1 + verbose];
        char *value = getenv(argv[1 + verbose]);

    if (verbose) 
    {
        if (value != NULL)
        printf("%s=%s\n", key, value);
    
        else
        printf("%s is NOT set!\n", key);
    }

    return value == NULL;

}
