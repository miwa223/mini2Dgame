#include "../inc/so_long.h"

int	main(int argc, char **argv)
{
	t_data	data;

	is_valid_argv(argc, argv);
	init_struct(&data, argv);
	display_images(&data);
	mlx_hook(data.mlx_win, 17, 0, close_window, &data);
	mlx_key_hook(data.mlx_win, press_key, &data);
	mlx_loop(data.mlx);
	return (0);
}
