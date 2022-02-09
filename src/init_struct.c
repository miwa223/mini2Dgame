/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:34:59 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 19:38:17 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_img(t_data *data, int flag)
{
	if (flag == 5)
		mlx_destroy_image(data->mlx, data->exit_img);
	if (flag == 5 || flag == 4)
		mlx_destroy_image(data->mlx, data->collect.img);
	if (flag == 5 || flag == 4 || flag == 3)
		mlx_destroy_image(data->mlx, data->wall_img);
	if (flag == 5 || flag == 4 || flag == 3 || flag == 2)
		mlx_destroy_image(data->mlx, data->bg.img);
	free(data->map.content);
	free_mlx(data);
	exit_program(XPM_TO_IMG_FAIL);
}

void	convert_xpm_to_image(t_data *data)
{
	data->bg.img = mlx_xpm_file_to_image(data->mlx,
			"images/background.xpm", &data->bg.size.x, &data->bg.size.y);
	if (!data->bg.img)
		free_img(data, 1);
	data->wall_img = mlx_xpm_file_to_image(data->mlx,
			"images/wall4.xpm", &data->img_size.x, &data->img_size.y);
	if (!data->wall_img)
		free_img(data, 2);
	data->collect.img = mlx_xpm_file_to_image(data->mlx,
			"images/collectible.xpm", &data->img_size.x, &data->img_size.y);
	if (!data->collect.img)
		free_img(data, 3);
	data->exit_img = mlx_xpm_file_to_image(data->mlx,
			"images/exit.xpm", &data->img_size.x, &data->img_size.y);
	if (!data->exit_img)
		free_img(data, 4);
	data->player.img = mlx_xpm_file_to_image(data->mlx,
			"images/player.xpm", &data->img_size.x, &data->img_size.y);
	if (!data->player.img)
		free_img(data, 5);
}

void	init_struct(t_data *data, char **argv)
{
	data->player.pos.x = 0;
	data->player.pos.y = 0;
	data->player.move = 0;
	data->player.set_done = false;
	set_map_info(argv, data);
	is_valid_map(&data->map);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data->map.content);
		exit_program(MLX_INIT_FAIL);
	}
	data->free_type = MLX;
	data->mlx_win = mlx_new_window(data->mlx, data->map.img_num.x * 31,
			data->map.img_num.y * 31, "so_long");
	if (!data->mlx_win)
	{
		free(data->map.content);
		free_mlx(data);
		exit_program(MLX_NEW_WINDOW_FAIL);
	}
	data->free_type = MLX_WIN;
	convert_xpm_to_image(data);
	data->free_type = MLX_WIN_IMG;
}
