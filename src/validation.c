#include "../inc/so_long.h"

void	is_valid_argv(int argc, char **argv)
{
	int		i;
	char	*str;

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
	if (!str || ft_strlen(str) != 4
		|| ft_strncmp(str, ".ber", ft_strlen(str)) != 0)
		exit_program(INVALID_ARG);
}

bool	check_first_last_line(t_data *data, int i, bool is_first, bool is_last)
{
	int	j;

	j = 0;
	while ((is_first || is_last) && data->map.img_num.x > j)
	{
		if (data->map.content[i] != WALL)
		{
			free(data->map.content);
			exit_program(INVALID_MAP);
		}
		i++;
		j++;
	}
     if (is_last && data->map.img_num.x == j)
        return (true);
    else
	    return (false);
}

bool    check_newline(t_data *data, int i, int *y, bool is_last)
{
    if (data->map.content[i - 1] != WALL || data->map.content[i + 1] != WALL)
    {
        free(data->map.content);
        exit_program(INVALID_MAP);
    }
    (*y)++;
    if (*y == data->map.img_num.y - 1)
        is_last = true;
    return (is_last);
}

void	is_valid_map(t_data *data)
{
    int i;
    int y;
    bool    is_first;
    bool    is_last;

    i = 0;
    y = 0;
    is_first = true;
    is_last = false;
    if (!ft_strchr(data->map.content, PLAYER)
        || !ft_strchr(data->map.content, COLLECT)
        || !ft_strchr(data->map.content, EXIT))
    {
        printf("passed\n");
        free(data->map.content);
        exit_program(INVALID_MAP);
    }
    while (data->map.content[i] != '\0')
    {
        if (check_first_last_line(data, i, is_first, is_last))
            break ;
        is_first = false;
        if (data->map.content[i] == '\n')
            is_last = check_newline(data, i, &y, is_last);
        else if (data->map.content[i] != PLAYER 
            && data->map.content[i] != COLLECT && data->map.content[i] != EXIT
            && data->map.content[i] != WALL && data->map.content[i] != SPACE)
        {
            free(data->map.content);
            exit_program(INVALID_MAP);
        }
        i++;
    }
}
