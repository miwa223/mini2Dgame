/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:35:52 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 00:35:53 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	display_images(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < data->map.img_num.x * 31 && y < data->map.img_num.y * 31)
	{
		while (x < data->map.img_num.x * 31)
		{
			mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->tail.img, x, y);
			x += data->tail.size.x;
		}
		x = 0;
		y += data->tail.size.y;
	}
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
		if (is_newline(data, &x, &y, &i))
			continue ;
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
		close_window(data);
	if ((key == A || key == S || key == D || key == W)
		&& move_to_wall(data, key))
		return (0);
	if (key == A)
		data->player.pos.x -= data->img_size.x;
	else if (key == S)
		data->player.pos.y += data->img_size.y;
	else if (key == D)
		data->player.pos.x += data->img_size.x;
	else if (key == W)
		data->player.pos.y -= data->img_size.y;
	if (key == A || key == S || key == D || key == W)
	{
		data->player.move += 1;
		printf("The current number of movements: %d\n", data->player.move);
	}
	display_images(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->player.img,
		data->player.pos.x, data->player.pos.y);
	return (0);
}
