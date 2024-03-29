/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:35:58 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 20:03:59 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

bool	is_newline(t_data *data, int *x, int *y, int *i)
{
	if (data->map.content[*i] == '\n')
	{
		*x = 0;
		*y += data->img_size.y;
		(*i)++;
		return (true);
	}
	return (false);
}

bool	is_collectible_with_player(t_data *data, int *x, int y, int *i)
{
	if (data->map.content[*i] == COLLECT)
	{
		if (*x == data->player.pos.x && y == data->player.pos.y)
		{
			data->map.content[*i] = '0';
			(*i)++;
			*x += data->img_size.x;
			data->collect.count++;
			return (true);
		}
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->collect.img,
			*x, y);
	}
	return (false);
}

void	is_exit(t_data *data, int x, int y, int i)
{
	if (data->map.content[i] == EXIT)
	{
		if (x == data->player.pos.x && y == data->player.pos.y
			&& data->collect.count == data->collect.total_num)
		{
			free(data->map.content);
			free_mlx(data);
			exit(EXIT_SUCCESS);
		}
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->exit_img,
			x, y);
	}
}

void	is_player(t_data *data, int x, int y, int i)
{
	if (data->map.content[i] == PLAYER)
	{
		if (!data->player.set_done)
		{
			data->player.pos.x = x;
			data->player.pos.y = y;
			mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->player.img, x, y);
			data->player.set_done = true;
		}
		data->map.content[i] = '0';
	}
}

void	put_sprites(t_data *data)
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
		if (data->map.content[i] == WALL)
			mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->wall_img, x, y);
		if (is_collectible_with_player(data, &x, y, &i))
			continue ;
		is_exit(data, x, y, i);
		is_player(data, x, y, i);
		x += data->img_size.x;
		i++;
	}
}
