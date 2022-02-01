#include "so_long.h"

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
	x = 0;
	y = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			x = 0;
			y += SPRITE_SIZE;
			i++;
			continue ;
		}
		if (map[i] == WALL)
		{
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->wall_img, x, y);
		}
		else if (map[i] == COLLECTIBLE)
		{
			if (x == current_chara_x && y == current_chara_y)
			{
				map[i] = '0';
				i++;
				x += 31;
				continue ;
			}
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->collect_img,
				x, y);
		}
		else if (map[i] == EXIT)
		{
			if (x == current_chara_x && y == current_chara_y)
			{
				exit(EXIT_SUCCESS);
			}
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->exit_img,
				x, y);
		}
		else if (map[i] == START_POSITION)
		{
			data->player.pos.x = x;
			data->player.pos.y = y;
		}
		x += 31;
		i++;
	}
}

int	display_sprites(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tail_img, 0, 0);
	put_sprites(data, data->map.content, x, y);
	return (0);
}

bool	condition_by_each_key(t_data *data, int key)
{
	if (key == A && data->map.content[i] == WALL && map_y == data->player.pos.y
		&& map_x == data->player.pos.x - data->img_size.x)
		return (true);
	else if (key == S && data->map.content[i] == WALL && map_x == data->player.pos.x
		&& map_y == data->player.pos.y + data->img_size.y)
		return (true);
	else if (key == D && data->map.content[i] == WALL && map_y == data->player.pos.y
		&& map_x == data->player.pos.x + data->img_size.x)
		return (true);
	else if (key == W && data->map.content[i] == WALL && map_x == data->player.pos.x
		&& map_y == data->player.pos.y - data->img_size.y)
		return (true);
	return (false);
}

bool	move_to_wall(t_data *data, int key)
{
	int	i;
	int	map_x;
	int	map_y;

	i = 0;
	map_x = 0;
	map_y = 0;
	while (data->map.content[i] != '\0')
	{
		if (data->map.content[i] == '\n')
		{
			map_x = 0;
			map_y += 31;
			i++;
			continue ;
		}
		if (condition_by_each_key(data, key))
			return (true);
		map_x += 31;
		i++;
	}
	return (false);
}

int	press_key(int key, t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (key == ESC)
		exit(EXIT_SUCCESS);
	if (key == A)
	{
		if (data->player.pos.x == data->img_size.x)
			return (0);
		if (move_to_wall(data, A))
			return (0);
		data->player.pos.x -= data->img_size.x;
	}
	else if (key == S)
	{
		if (data->player.pos.y == data->img_size.y * (data->map.img_num.y - 2))
			return (0);
		if (move_to_wall(data, S))
			return (0);
		data->player.pos.y += data->img_size.y;
	}
	else if (key == D)
	{
		if (data->player.pos.x == data->img_size.x * (data->map.img_num.x - 2))
			return (0);
		if (move_to_wall(data, D))
			return (0);
		data->player.pos.x += data->img_size.x;
	}
	else if (key == W)
	{
		if (data->player.pos.y == data->img_size.y)
			return (0);
		if (move_to_wall(data, W))
			return (0);
		data->player.pos.y -= data->img_size.y;
	}
	if (key == A || key == S || key == D || key == W)
	{
		data->player.move_count += 1;
		printf("The current number of movements: %d\n", data->player.move_count);
	}
	x = data->player.pos.x;
	y = data->player.pos.y;
	// mlx_clear_window(data->mlx, data->window.mlx_win);
	display_sprites(data, x, y);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->player.img, x, y);
	data->player.pos.x = x;
	data->player.pos.y = y;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	is_valid_argv(argc, argv);
	init_struct(&data, argv);
	display_sprites(&data, 0, 0); //これ不要かも
	mlx_hook(data.mlx_win, 17, 0, close_window, 0);
	mlx_key_hook(data.mlx_win, press_key, &data);
	mlx_loop(data.mlx);
	return (0);
}
