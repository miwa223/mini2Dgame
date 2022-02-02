/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 00:37:04 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/02/03 00:37:06 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "get_next_line.h"

# define WALL '1'
# define COLLECT 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define SPACE '0'
# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 65307
# define SPRITE_SIZE 31
# define ERROR "Error\n"

typedef enum e_error{
	INVALID_ARG,
	MLX_INIT_FAIL,
	MLX_NEW_WINDOW_FAIL,
	XPM_TO_IMG_FAIL,
	MALLOC_FAIL,
	READ_FAIL,
	CLOSE_FAIL,
	INVALID_MAP
}				t_error;

typedef enum e_free{
	MLX,
	MLX_WIN,
	MLX_WIN_IMG
}				t_free;

typedef struct s_xy{
	int	x;
	int	y;
}				t_xy;

typedef struct s_player{
	void	*img;
	t_xy	pos;
	int		move;
}				t_player;

typedef struct s_tail{
	void	*img;
	t_xy	size;
}				t_tail;
typedef struct s_map{
	char	*content;
	t_xy	img_num;
}				t_map;

typedef struct s_data{
	void	*mlx;
	void	*mlx_win;
	t_tail	tail;
	void	*wall_img;
	void	*collect_img;
	void	*exit_img;
	t_player	player;
	t_xy	img_size;
	t_map	map;
	int		free_type;
}				t_data;

void	is_valid_argv(int argc, char **argv);
void	check_character_inclusion(t_map *map);
bool	check_first_last_line(t_map *map, int i, bool is_first, bool is_last);
bool	count_line(t_map *map, int i, int *line_num, bool is_last);
void	is_valid_map(t_map *map);
bool	concat_map(char **map, char *line, bool first_time);
void	get_map(char **map, int fd);
void	read_map(char **argv, char **map);
int		count_to_eof(t_map *map, int i);
void	count_img_num_on_xy_axis(t_map *map);
void	convert_xpm_to_image(t_data *data);
void	init_struct(t_data *data, char **argv);

int		display_images(t_data *data);
bool	judge_by_key(t_data *data, int key, int x, int y);
bool	move_to_wall(t_data *data, int key);
int		press_key(int key, t_data *data);

bool	is_newline(t_data *data, int *x, int *y, int *i);
bool	is_collectible_with_player(t_data *data, int *x, int y, int *i);
void	is_exit(t_data *data, int x, int y, int i);
void	is_start_position(t_data *data, int x, int y, int i);
void	put_sprites(t_data *data);

void	free_mlx(t_data *data);
int		close_window(t_data *data);
void	exit_program(int error_type);

#endif
