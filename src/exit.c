/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:35:27 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 19:07:41 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_mlx(t_data *data)
{
	if (data->free_type == MLX_WIN_IMG)
	{
		mlx_destroy_image(data->mlx, data->bg.img);
		mlx_destroy_image(data->mlx, data->wall_img);
		mlx_destroy_image(data->mlx, data->collect.img);
		mlx_destroy_image(data->mlx, data->exit_img);
		mlx_destroy_image(data->mlx, data->player.img);
	}
	if (data->free_type == MLX_WIN_IMG || data->free_type == MLX_WIN)
		mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

int	close_window(t_data *data)
{
	free(data->map.content);
	free_mlx(data);
	exit(EXIT_SUCCESS);
}

void	exit_program(int error_type)
{
	if (error_type == INVALID_ARG)
		printf("Error\nInvalid arguments\n");
	else if (error_type == MLX_INIT_FAIL)
		printf("Error\nMlx initialization failed\n");
	else if (error_type == MLX_NEW_WINDOW_FAIL)
		printf("Error\nMlx window creation failed\n");
	else if (error_type == XPM_TO_IMG_FAIL)
		printf("Error\nXpm to image conversion failed\n");
	else if (error_type == MALLOC_FAIL)
		printf("Error\nMalloc failed\n");
	else if (error_type == OPEN_FAIL)
		printf("Error\nOpen failed\n");
	else if (error_type == READ_FAIL)
		printf("Error\nRead failed\n");
	else if (error_type == CLOSE_FAIL)
		printf("Error\nClose map\n");
	else if (error_type == INVALID_MAP)
		printf("Error\nInvalid map\n");
	exit(EXIT_FAILURE);
}
