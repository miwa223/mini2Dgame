#include "so_long.h"

void    exit_program(void)
{
    printf("%s", ERROR);
    exit(EXIT_FAILURE);
}

void    is_valid_argv(int argc, char **argv)
{
    int i;

    i = 0;
    if (argc != 2)
        exit_program();
    while (argv[1][i] != '\0' && argv[1][i] != '.')
    {
        i++;
    }
    // if (argv[1][i] != ".bat")
    //     exit_program();
}