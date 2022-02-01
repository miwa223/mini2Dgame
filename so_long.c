#include "so_long.h"

int	close_window(void)
{
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	is_valid_argv(argc, argv);
	init_struct(&data, argv);
	display_images(&data); //これ不要かも
	mlx_hook(data.mlx_win, 17, 0, close_window, 0);
	mlx_key_hook(data.mlx_win, press_key, &data);
	mlx_loop(data.mlx);
	return (0);
}
