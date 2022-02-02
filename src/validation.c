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
		if (argv[1][i] == '.');
		str = &argv[1][i];
		i++;
	}
	if (!str || ft_strlen(str) != 4
		|| ft_strncmp(str, ".ber", ft_strlen(str)) != 0)
		exit_program(INVALID_ARG);
}

bool	check_first_and_last_line(t_data *data, int i, bool first_last)
{
	int	j;

	j = 0;
	while ((first_last) && data->map.img_num.x > j)
	{
		if (data->map.content[i] != WALL)
		{
			free(data->map.content);
			exit_program(INVALID_MAP);
		}
		i++;
		j++;
	}
	return (false);
}

void	is_valid_map(t_data *data)
{
    int i;
    int y;
    int player_num;
    int collect_num;
    int exit_num;
    bool    first_last;

    i = 0;
    y = 0;
    player_num = 0;
    collect_num = 0;
    exit_num = 0;
    first_last = true;
    while (data->map.content[i] != '\0')
    {
        // while ((first_line || last_line) && data->map.img_num.x > j)
        // {
        //     if (data->map.content[i] != WALL)
        //     {
        //         free(data->map.content);
        //         exit_program(INVALID_MAP);
        //     }
        //     i++;
        //     j++;
        // }
		first_last = check_first_and_last_line(data, i, first_last);
        if (last_line && (data->map.img_num.x == j))
            break ;
        if (data->map.content[i] == '\n')
        {
            if (data->map.content[i - 1] != WALL || data->map.content[i + 1] != WALL)
            {
                free(data->map.content);
                exit_program(INVALID_MAP);
            }
            y++;
            if (y == data->map.img_num.y - 1)
                last_line = true;
        }
        else if (data->map.content[i] == START_POSITION)
            player_num++;
        else if (data->map.content[i] == COLLECTIBLE)
            collect_num++;
        else if (data->map.content[i] == EXIT)
            exit_num++;
        else if (data->map.content[i] != WALL && data->map.content[i] != SPACE)
        {
            free(data->map.content);
            exit_program(INVALID_MAP);
        }
        i++;
    }
    if (!player_num || collect_num == 0 || exit_num == 0)
    {
        free(data->map.content);
        exit_program(INVALID_MAP);
    }
}
