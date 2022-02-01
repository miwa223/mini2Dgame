#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include "libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
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
    int	    move;
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

void    exit_program(void);
void    is_valid_argv(int argc, char **argv);
void	read_map(char **argv, char **map);
void	count_img_num_on_xy_axis(t_map *map);
void	convert_xpm_to_image(t_data *data);
void	init_struct(t_data *data, char **argv);

int	display_images(t_data *data);
bool	judge_by_key(t_data *data, int key, int x, int y);
bool	move_to_wall(t_data *data, int key);
int	press_key(int key, t_data *data);

bool	is_newline(t_data *data, int *x, int *y, int *i);
bool	is_collectible_with_player(t_data *data, int *x, int y, int *i);
void	is_exit(t_data *data, int x, int y, int i);
void	is_start_position(t_data *data, int x, int y, int i);
void	put_sprites(t_data *data);

#endif
