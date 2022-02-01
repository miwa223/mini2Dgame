#include "so_long.h"

void	init_struct(t_data *data, int y_count, int x_count)
{
	data->mlx = mlx_init();
	data->window.size.x = x_count * 31;
	data->window.size.y = y_count * 31;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.move_count = 0;
	data->wall.pos_x = 0;
	data->wall.pos_y = 0;
	data->collect.pos_x = 0;
	data->collect.pos_y = 0;
	data->exit.pos_x = 0;
	data->exit.pos_y = 0;
}

int	close_window(void)
{
	exit(EXIT_SUCCESS);
}

void	put_sprites(t_data *data, char *map, int current_chara_x, int current_chara_y)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = -31;
	y = 0;
	while (map[i] != '\0')
	{
		if (map[i] == WALL)
		{
			data->wall.pos_x = x;
			data->wall.pos_x += SPRITE_SIZE;
			data->wall.pos_y = y;
			x = data->wall.pos_x;
			y = data->wall.pos_y;
			mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->wall.img,
				data->wall.pos_x, data->wall.pos_y);
		}
		else if (map[i] == '\n')
		{
			x = -31;
			y += SPRITE_SIZE;
		}
		else if (map[i] == COLLECTIBLE)
		{
			data->collect.pos_x = x;
			data->collect.pos_x += SPRITE_SIZE;
			data->collect.pos_y = y;
			x = data->collect.pos_x;
			y = data->collect.pos_y;
			if (x == current_chara_x && y == current_chara_y)
			{
				map[i] = '0';
				i++;
				continue ;
			}
			mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->collect.img,
				data->collect.pos_x, data->collect.pos_y);
		}
		else if (map[i] == EXIT)
		{
			data->exit.pos_x = x;
			data->exit.pos_x += SPRITE_SIZE;
			data->exit.pos_y = y;
			x = data->exit.pos_x;
			y = data->exit.pos_y;
			if (x == current_chara_x && y == current_chara_y)
			{
				exit(EXIT_SUCCESS);
			}
			mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->exit.img,
				data->exit.pos_x, data->exit.pos_y);
		}
		else if (map[i] == START_POSITION)
		{
			data->player.pos_x = x;
			data->player.pos_x += SPRITE_SIZE;
			data->player.pos_y = y;
			x = data->player.pos_x;
			y = data->player.pos_y;
		}
		else
			x += 31;
		i++;
	}
	printf("--------------------------------------\n");
}

int	display_sprites(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->tail.img, 0, 0);
	put_sprites(data, data->map.content, x, y);
	return (0);
}

int	press_key(int key, t_data *data)
{
	int x;
	int y;
	int	i;
	int	map_x;
	int	map_y;

	x = 0;
	y = 0;
	i = 0;
	map_x = 0;
	map_y = 0;
	if (key == ESC)
		exit(EXIT_SUCCESS);
	//wallにぶつかる判定がtrueの場合、returnする（必要な情報：player.pos_x, player.pos_y, wall's position)
	//wall's positionの求め方(関数作るといいかも)
	// 現在のplayerの座標を元に動く方向＋31の位置にwallがあるかチェック
	// このチェックは、data.map.content[0]〜最初の改行までx+31, 改行見つかったらy+=31, x=0に設定してループする
	// で、player+31の座標と一致したらreturn
	if (key == A)
	{
		if (data->player.pos_x == data->player.size.x)
			return (0);
		while (data->map.content[i] != '\0')
		{
			if (data->map.content[i] == '\n')
			{
				map_x = 0;
				map_y += 31;
				i++;
				continue ;
			}
			if (data->map.content[i] == WALL && map_y == data->player.pos_y
				&& map_x == data->player.pos_x - data->player.size.x)
			{
				return (0);
			}
			map_x += 31;
			i++;
		}
		data->player.pos_x -= data->player.size.x;
	}
	else if (key == S)
	{
		if (data->player.pos_y == data->player.size.y * (data->map.size.y - 2)) //y_count - 2 = 2
			return (0);
		data->player.pos_y += data->player.size.y;
	}
	else if (key == D)
	{
		if (data->player.pos_x == data->player.size.x * (data->map.size.x - 2)) //x_count - 2 = 7
			return (0);
		data->player.pos_x += data->player.size.x;
	}
	else if (key == W)
	{
		if (data->player.pos_y == data->player.size.y)
			return (0);
		data->player.pos_y -= data->player.size.y;
	}
	if (key == A || key == S || key == D || key == W)
	{
		data->player.move_count += 1;
		printf("The current number of movements: %d\n", data->player.move_count);
	}
	x = data->player.pos_x;
	y = data->player.pos_y;
	// mlx_clear_window(data->mlx, data->window.mlx_win);
	display_sprites(data, x, y);
	mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->player.img, x, y);
	data->player.pos_x = x;
	data->player.pos_y = y;
	return (0);
}

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

void	calc_newline(char *map, int *y_count, int *x_count)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	*y_count = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			*y_count += 1;
			if (flag == 0)
			{
				*x_count = i;
				flag = 1;
			}
		}
		i++;
	}
	*y_count += 1;
}

void	convert_xpm_to_image(t_data *data)
{
	char	*player_path;
	char	*wall_path;
	char	*tail_path;
	char	*collect_path;
	char	*exit_path;

	player_path = "images/player.xpm";
	wall_path = "images/wall.xpm";
	tail_path = "images/tail.xpm";
	collect_path = "images/collectible.xpm";
	exit_path = "images/exit.xpm";
	data->tail.img = mlx_xpm_file_to_image(data->mlx, tail_path,
		&data->tail.size.x, &data->tail.size.y);
	data->player.img = mlx_xpm_file_to_image(data->mlx, player_path,
		&data->player.size.x, &data->player.size.y);
	data->wall.img = mlx_xpm_file_to_image(data->mlx, wall_path,
		&data->wall.size.x, &data->wall.size.y);
	data->collect.img = mlx_xpm_file_to_image(data->mlx, collect_path,
		&data->collect.size.x, &data->collect.size.y);
	data->exit.img = mlx_xpm_file_to_image(data->mlx, exit_path,
		&data->exit.size.x, &data->exit.size.y);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int	y_count;
	int	x_count;
    char    *map;

	is_valid_argv(argc, argv);
	read_map(argv, &map);
	calc_newline(map, &y_count, &x_count);
	init_struct(&data, y_count, x_count);
	data.map.content = map;
	data.map.size.x = x_count;
	data.map.size.y = y_count;
	data.window.mlx_win = mlx_new_window(data.mlx, data.window.size.x, data.window.size.y, "so_long");
	convert_xpm_to_image(&data);
	display_sprites(&data, 0, 0);
	mlx_hook(data.window.mlx_win, 17, 0, close_window, 0);
	mlx_key_hook(data.window.mlx_win, press_key, &data);
	// mlx_sync(2, data.mlx_win);
	// mlx_loop_hook(data.mlx, display_sprites, &data);
	mlx_loop(data.mlx);
	return (0);
}
