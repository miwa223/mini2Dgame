#include "so_long.h"

void	init_struct(t_data *data, int newline_count, int x_count)
{
	data->mlx = mlx_init();
	data->window.size_x = x_count * 31;
	data->window.size_y = (newline_count + 1) * 31;
	data->character.position_x = 0; //starting position
	data->character.position_y = 0;
	data->character.move_count = 0;
	data->wall.position_x = 0;
	data->wall.position_y = 0;
	data->present.position_x = 0;
	data->present.position_y = 0;
	data->boat.position_x = 0;
	data->boat.position_y = 0;
	data->count = 0;
}

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

int	close_window(void)
{
	exit(EXIT_SUCCESS);
}

//just for checking the key number
int	press_esc(int key, t_data *data)
{
	(void)data;
	printf("esc pressed: %d\n", key);
	return (0);
}

void	put_sprites(t_data *data, char *map)
{
	int	i;
	int	x;
	int	y;
	// void	*img;

	i = 0;
	x = -31;
	y = 0;
	printf("--------------------------------------\n");
	while (map[i] != '\0')
	{
		// printf("map[%d]; %c\n", i, map[i]);
		if (map[i] == '1')
		{
			data->wall.position_x = x;
			data->wall.position_x += SPRITE_SIZE;
			data->wall.position_y = y;
			x = data->wall.position_x;
			y = data->wall.position_y;
			// printf("x_; %d\n", data->wall.position_x);
			// printf("y_; %d\n", data->wall.position_y);
			mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->wall.img,
				data->wall.position_x, data->wall.position_y);
		}
		else if (map[i] == '\n')
		{
			x = -31;
			y += SPRITE_SIZE;
		}
		else if (map[i] == 'C')
		{
			data->present.position_x = x;
			data->present.position_x += SPRITE_SIZE;
			data->present.position_y = y;
			x = data->present.position_x;
			y = data->present.position_y;
			mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->present.img,
				data->present.position_x, data->present.position_y);
		}
		else if (map[i] == 'E')
		{
			data->boat.position_x = x;
			data->boat.position_x += SPRITE_SIZE;
			data->boat.position_y = y;
			x = data->boat.position_x;
			y = data->boat.position_y;
			mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->boat.img,
				data->boat.position_x, data->boat.position_y);
		}
		else if (map[i] == 'P')
		{
			data->character.position_x = x;
			data->character.position_x += SPRITE_SIZE;
			data->character.position_y = y;
			x = data->character.position_x;
			y = data->character.position_y;
			// mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->character.img,
			// 	data->character.position_x, data->character.position_y);
		}
		else
		{
			x += 31;
		}
		// printf("x; %d\n", x);
		// printf("y; %d\n", y);
		i++;
	}
	printf("--------------------------------------\n");
}

int	display_sprites(t_data *data)
{
	// printf("count; %d\n", data->count);
	// printf("map; %s\n", data->map);
	// data->count += 1;
	// if (data->count == 100)
	// {
	mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->tail.img, 0, 0);
	put_sprites(data, data->map);
	// mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->character.img,
	// 	data->character.position_x, data->character.position_y);
		// data->count = 0;
	// }
	return (0);
}

//for esc key and main character's move
int	press_key(int key, t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (key == 65307)
		exit(EXIT_SUCCESS);
	// mlx_clear_window(data->mlx, data->window.mlx_win);
	printf("_x; %d, y; %d\n", data->character.position_x, data->character.position_y);
	if (key == 97) // A
	{
		if (data->character.position_x == data->character.size_x)
		{
			printf("A\n");
			return (0);
		}
		data->character.position_x -= data->character.size_x;
		printf("A x; %d, y; %d\n", data->character.position_x, data->character.position_y);
	}
	else if (key == 115) //S
	{
		if (data->character.position_y == data->character.size_y * 2) //newline_count - 1 = 2
			return (0);		
		data->character.position_y += data->character.size_y;
		printf("S x; %d, y; %d\n", data->character.position_x, data->character.position_y);
	}
	else if (key == 100) //D
	{
		printf("chara_pos; %d\n", data->character.position_x);
		printf("win; %d\n", data->window.size_x);
		printf("chara_size; %d\n", data->character.size_x);
		if (data->character.position_x == data->character.size_x * 7) //x_count - 2 = 7
			return (0);
		data->character.position_x += data->character.size_x;
		printf("D x; %d, y; %d\n", data->character.position_x, data->character.position_y);
	}
	else if (key == 119) //W
	{
		if (data->character.position_y == data->character.size_y)
			return (0);
		data->character.position_y -= data->character.size_y;
		printf("W x; %d, y; %d\n", data->character.position_x, data->character.position_y);
	}
	if (key == 97 || key == 115 || key == 100 || key == 119)
	{
		data->character.move_count += 1;
		printf("The current number of movements: %d\n", data->character.move_count);
	}
	x = data->character.position_x;
	y = data->character.position_y;
	// mlx_clear_window(data->mlx, data->window.mlx_win);
	display_sprites(data);
	mlx_put_image_to_window(data->mlx, data->window.mlx_win, data->character.img,
				x, y);
	data->character.position_x = x;
	data->character.position_y = y;
	return (0);
}


void	read_map(char **argv, char **map)
{
	int	fd;
	int	i;
	char *line;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		if (i == 0)
			*map = line;
		else
			*map = ft_strjoin(*map, line);
		*map = ft_strjoin(*map, "\n");
		i++;
		printf("OK; %s\n", *map);
	}
	*map = ft_strjoin(*map, line);
	free(line);
	close(fd);
}

void	calc_newline(char *map, int *newline_count, int *x_count)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	*newline_count = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			*newline_count += 1;
			if (flag == 0)
			{
				*x_count = i;
				flag = 1;
			}
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	*character_path = "images/character.xpm";
	char	*wall_path = "images/Wall.xpm";
	char	*tail_path = "images/solidcolor.xpm";
	char	*present_path = "images/present.xpm";
	char	*boat_path = "images/boat.xpm";
	int	newline_count;
	int	x_count;
    char    *map;


	is_valid_argv(argc, argv);
	read_map(argv, &map);
	calc_newline(map, &newline_count, &x_count);
	init_struct(&data, newline_count, x_count);
	data.map = map;

	data.window.mlx_win = mlx_new_window(data.mlx, data.window.size_x, data.window.size_y, "so_long"); //1920, 1080
	data.tail.img = mlx_xpm_file_to_image(data.mlx, tail_path,
		&data.window.size_x, &data.window.size_y);
	data.character.img = mlx_xpm_file_to_image(data.mlx, character_path,
		&data.character.size_x, &data.character.size_y);
	data.wall.img = mlx_xpm_file_to_image(data.mlx, wall_path,
		&data.wall.size_x, &data.wall.size_y);
	data.present.img = mlx_xpm_file_to_image(data.mlx, present_path,
		&data.present.size_x, &data.present.size_y);
	data.boat.img = mlx_xpm_file_to_image(data.mlx, boat_path,
		&data.boat.size_x, &data.boat.size_y);
	
	display_sprites(&data);
	mlx_hook(data.window.mlx_win, 17, 0, close_window, 0);
	mlx_key_hook(data.window.mlx_win, press_key, &data);
	// mlx_sync(2, data.mlx_win);
	// mlx_loop_hook(data.mlx, display_sprites, &data);
	mlx_loop(data.mlx);
	return (0);
}
