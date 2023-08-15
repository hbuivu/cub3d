#include "../include/cub3D.h"

void	init_main(t_main *main)
{
	main->win_width = 1344;
	main->win_height = 1000;
	main->n_angle = M_PI / 2;
	main->s_angle = (3 * M_PI) / 2;
	main->e_angle = 2 * M_PI;
	main->w_angle = M_PI;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_main	*main;
	t_omap	*map_ptr;

	error_check(argc, argv);
	main = NULL;
	main = cub_calloc(1, sizeof(t_main), main);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return_error(main, OPEN_ERR);
	download_map(fd, main); //fills out omap
	map_ptr = identify(main->omap, main); //fills out everything else in main
	parse_map(map_ptr, main);
	get_map(map_ptr, main);
	// print_main_map(main);
	check_walled(main);
	init_main(main);
	init_calc(main);
	// print_main(main);
	mlx(main);
	// raycast(main);
	// return_error(main, NONE);
}
