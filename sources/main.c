#include "../include/cub3D.h"

void	init_main(t_main *main)
{
	main->win_width = 320;
	main->win_height = 200;
	main->calc = (t_calc *)cub_calloc(1, sizeof(t_calc), main);
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
	// print_omap(main->omap);
	map_ptr = identify(main->omap, main);//fills out everything else in main
	parse_map(map_ptr, main); //puts map in main
	get_map(map_ptr, main);
	// print_main_map(main);
	check_walled(main);
	// init_main(main);
	// raycast(main);
	// print_calc(main);
	return_error(main, NONE);
}
