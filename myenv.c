#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
 {
    size_t i = 0;
    for (; envp[i] != NULL; ++i) 
    {
        printf("%s\n", envp[i]);
    }

    printf("There are %zu set Variables!\n", i);
}