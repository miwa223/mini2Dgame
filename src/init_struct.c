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

void	read_map(char **argv, char **map)
{
	int		fd;
	int		status;
	char	*line;
	char	*tmp;
	bool	first_time;

	first_time = true;
	fd = open(argv[1], O_RDONLY);
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
	if (close(fd) == -1)
	{
		free(*map);
		exit_program(CLOSE_FAIL);
	}
}

void	count_img_num_on_xy_axis(t_map *map)
{
	int		i;
	bool	counted;

	i = 0;
	counted = false;
	map->img_num.y = 0;
	while (map->content[i] != '\0')
	{
		if (map->content[i] == '\n')
		{
			if (!counted)
			{
				map->img_num.x = i;
				counted = true;
			}
			else if (counted && i - (map->img_num.x + 1) * map->img_num.y != map->img_num.x)
			{
				free(map->content);
				exit_program(INVALID_MAP);
			}
			map->img_num.y += 1;
			printf("x; %d, y; %d\n", map->img_num.x, map->img_num.y);
		}
		i++;
	}
	if (map->content[i - 1] != '\n')
	{
		if (i - (map->img_num.x + 1) * map->img_num.y != map->img_num.x)
		{
			free(map->content);
			exit_program(INVALID_MAP);
		}
		map->img_num.y += 1;
	}
	printf("x; %d, y; %d\n", map->img_num.x, map->img_num.y);
}

void	convert_xpm_to_image(t_data *data)
{
	data->tail.img = mlx_xpm_file_to_image(data->mlx,
			"images/tail.xpm", &data->tail.size.x, &data->tail.size.y);
	data->wall_img = mlx_xpm_file_to_image(data->mlx,
			"images/wall.xpm", &data->img_size.x, &data->img_size.y);
	data->collect_img = mlx_xpm_file_to_image(data->mlx,
			"images/collectible.xpm", &data->img_size.x, &data->img_size.y);
	data->exit_img = mlx_xpm_file_to_image(data->mlx,
			"images/exit.xpm", &data->img_size.x, &data->img_size.y);
	data->player.img = mlx_xpm_file_to_image(data->mlx,
			"images/player.xpm", &data->img_size.x, &data->img_size.y);
	if (!data->tail.img || !data->wall_img || !data->collect_img
		|| !data->exit_img || !data->player.img)
	{
		free_mlx(data);
		exit_program(XPM_TO_IMG_FAIL);
	}
}

void	init_struct(t_data *data, char **argv)
{
	data->player.pos.x = 0;
	data->player.pos.y = 0;
	data->player.move = 0;
	read_map(argv, &data->map.content);
	count_img_num_on_xy_axis(&data->map);
	is_valid_map(&data->map);
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_program(MLX_INIT_FAIL);
	data->free_type = MLX;
	data->mlx_win = mlx_new_window(data->mlx, data->map.img_num.x * 31,
			data->map.img_num.y * 31, "so_long");
	if (!data->mlx_win)
	{
		free_mlx(data);
		exit_program(MLX_NEW_WINDOW_FAIL);
	}
	data->free_type = MLX_WIN;
	convert_xpm_to_image(data);
	data->free_type = MLX_WIN_IMG;
}
