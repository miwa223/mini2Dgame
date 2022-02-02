#include "../inc/so_long.h"

void    exit_program(int error_type)
{
    if (error_type == INVALID_ARG)
        printf("Error\nInvalid arguments\n");
    exit(EXIT_FAILURE);
}

void    is_valid_argv(int argc, char **argv)
{
    int i;
    char    *str;

    i = 0;
    str = NULL;
    if (argc != 2)
        exit_program(INVALID_ARG);
    while (argv[1][i] != '\0')
    {
        if (argv[1][i] == '.')
            str = &argv[1][i];
        i++;
    }
    if (!str || ft_strncmp(str, ".ber", ft_strlen(str)) != 0)
        exit_program(INVALID_ARG);
}