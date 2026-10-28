#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) 
{
for (size_t i = 1; i < argc; i++) 
{
    printf("%s ", argv[i]);
}

printf("\n");

}