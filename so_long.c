#include "so_long.h"

int	close_window(void)
{
	exit(EXIT_SUCCESS);
}

int	display_images(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->tail_img, 0, 0);
	put_sprites(data);
	return (0);
}

bool	judge_by_key(t_data *data, int key, int x, int y)
{
	if (key == A && y == data->player.pos.y
		&& x == data->player.pos.x - data->img_size.x)
		return (true);
	else if (key == S && x == data->player.pos.x
		&& y == data->player.pos.y + data->img_size.y)
		return (true);
	else if (key == D && y == data->player.pos.y
		&& x == data->player.pos.x + data->img_size.x)
		return (true);
	else if (key == W && x == data->player.pos.x
		&& y == data->player.pos.y - data->img_size.y)
		return (true);
	return (false);
}

bool	move_to_wall(t_data *data, int key)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	while (data->map.content[i] != '\0')
	{
		if (data->map.content[i] == '\n')
		{
			x = 0;
			y += 31;
			i++;
			continue ;
		}
		if (data->map.content[i] == WALL && judge_by_key(data, key, x, y))
			return (true);
		x += 31;
		i++;
	}
	return (false);
}

int	press_key(int key, t_data *data)
{
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
	// mlx_clear_window(data->mlx, data->window.mlx_win);
	display_images(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->player.img, data->player.pos.x, data->player.pos.y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	is_valid_argv(argc, argv);
	init_struct(&data, argv);
	display_images(&data); //これ不要かも
	mlx_hook(data.mlx_win, 17, 0, close_window, 0);
	mlx_key_hook(data.mlx_win, press_key, &data);
	mlx_loop(data.mlx);
	return (0);
}
