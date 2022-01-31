#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include "get_next_line.h"

# define ERROR "Error\n"
# define SPRITE_SIZE 31

typedef struct s_image{
    void    *img;
    int size_x;
    int size_y;
    int position_x;
    int position_y;
    char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     move_count;
}               t_image;

typedef struct s_window{
    void *mlx_win;
    int size_x;
    int size_y;
}               t_window;

typedef struct s_data{
    void    *mlx;
    int count;
    t_window    window;
    t_image tail;
    t_image wall;
    t_image character;
    t_image present;
    t_image boat;
    char *map;
}               t_data;

// void	init_struct(t_data *data);
void    exit_program(void);
void    is_valid_argv(int argc, char **argv);

#endif