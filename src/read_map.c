#include "../inc/so_long.h"

bool	concat_map(char **map, char *line, bool first_time)
{
	char	*tmp;

	if (first_time)
	{
		*map = line;
		first_time = false;
	}
	else
	{
		tmp = *map;
		*map = ft_strjoin(*map, line);
		free(tmp);
		free(line);
	}
	tmp = *map;
	*map = ft_strjoin(*map, "\n");
	free(tmp);
	return (first_time);
}

void	get_map(char **map, int fd)
{
	char	*line;
	char	*tmp;
	int		status;
	bool	first_time;

	first_time = true;
	status = get_next_line(fd, &line);
	if (status == 0)
		*map = line;
	while (status == 1)
	{
		first_time = concat_map(map, line, first_time);
		if (get_next_line(fd, &line) == 0)
		{
			tmp = *map;
			*map = ft_strjoin(*map, line);
			free(tmp);
			free(line);
			break ;
		}
	}
}

void	read_map(char **argv, char **map)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	get_map(map, fd);
	if (close(fd) == -1)
	{
		free(*map);
		exit_program(CLOSE_FAIL);
	}
}
