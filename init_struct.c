#include "so_long.h"

void	read_map(char **argv, char **map)
{
	int	fd;
	int	i;
	char *line;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (i == 0)
			*map = line;
		else
			*map = ft_strjoin(*map, line);
		*map = ft_strjoin(*map, "\n");
		i++;
	}
	*map = ft_strjoin(*map, line);
	free(line);
	close(fd);
}

void	count_img_num_on_xy_axis(t_map *map)
{
	int	i;
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
			map->img_num.y += 1;
		}
		i++;
	}
	map->img_num.y += 1;
}

void	convert_xpm_to_image(t_data *data)
{
	data->tail_img = mlx_xpm_file_to_image(data->mlx,
	"images/tail.xpm", &data->img_size.x, &data->img_size.y);
	data->wall_img = mlx_xpm_file_to_image(data->mlx,
	"images/wall.xpm", &data->img_size.x, &data->img_size.y);
	data->collect_img = mlx_xpm_file_to_image(data->mlx,
	"images/collectible.xpm", &data->img_size.x, &data->img_size.y);
	data->exit_img = mlx_xpm_file_to_image(data->mlx,
	"images/exit.xpm", &data->img_size.x, &data->img_size.y);
	data->player.img = mlx_xpm_file_to_image(data->mlx,
	"images/player.xpm", &data->img_size.x, &data->img_size.y);
}

void	init_struct(t_data *data, char **argv)
{
	data->mlx = mlx_init();
	data->player.pos.x = 0;
	data->player.pos.y = 0;
	data->player.move = 0;
	read_map(argv, &data->map.content);
	count_img_num_on_xy_axis(&data->map);
	data->mlx_win = mlx_new_window(data->mlx, data->map.img_num.x * 31,
		data->map.img_num.y * 31, "so_long");
	convert_xpm_to_image(data);
}
