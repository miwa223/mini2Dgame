/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:34:59 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 00:35:08 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	count_to_eof(t_map *map, int i)
{
	bool	counted;

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
			else if (counted
				&& i - (map->img_num.x + 1) * map->img_num.y != map->img_num.x)
			{
				free(map->content);
				exit_program(INVALID_MAP);
			}
			map->img_num.y += 1;
		}
		i++;
	}
	return (i);
}

void	count_img_num_on_xy_axis(t_map *map)
{
	int		i;

	i = 0;
	i = count_to_eof(map, i);
	if (map->content[i - 1] != '\n')
	{
		if (i - (map->img_num.x + 1) * map->img_num.y != map->img_num.x)
		{
			free(map->content);
			exit_program(INVALID_MAP);
		}
		map->img_num.y += 1;
	}
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
