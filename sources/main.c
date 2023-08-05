#include "../include/cub3D.h"

void	init_main(t_main *main)
{
	main->win_width = 320;
	main->win_height = 200;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_main	*main;
	// t_omap	*map_ptr;

	error_check(argc, argv);
	main = NULL;
	main = cub_calloc(1, sizeof(t_main), main);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("error\n not a file");
		return_error(main, OPEN_ERR);
	}
	download_map(fd, main); //fills out omap
	// map_ptr = identify(main->omap, main);
	parse_map(main->omap, main); //fills out everything else in main
	init_main(main);
	init_calc(main);
	// print_main(main);
	raycast(main);
	return_error(main, NONE);
}
