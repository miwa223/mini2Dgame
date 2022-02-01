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

# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define START_POSITION 'P'
# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 65307
# define SPRITE_SIZE 31
# define ERROR "Error\n"

typedef struct s_xy{
	int	x;
	int	y;
}				t_xy;

typedef struct s_player{
    void    *img;
    t_xy    pos;
    int	    move_count;
}               t_player;

typedef struct s_map{
	char	*content;
    t_xy    img_num;
}				t_map;

typedef struct s_data{
    void    *mlx;
    void    *mlx_win;
    void    *tail_img;
    void    *wall_img;
    void    *collect_img;
    void    *exit_img;
    t_player player;
    t_xy    img_size;
	t_map	map;
}               t_data;

// void	init_struct(t_data *data);
void    exit_program(void);
void    is_valid_argv(int argc, char **argv);

#endif
