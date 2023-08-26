#include "../include/cub3D.h"

void	parse_cub(int fd, t_main *main)
{
	t_omap	*begin_map;

	download_map(fd, main);
	begin_map = identify(main->omap, main); //check all elements
	check_map(begin_map, main); //check map
	get_map(begin_map, main);
	check_walled(main);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_main	*main;

	error_check(argc, argv);
	main = NULL;
	main = cub_calloc(1, sizeof(t_main), main);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return_error(main, OPEN_ERR);
	parse_cub(fd, main);
	init_calc(main);
	printf("ORIG px: %lf py: %lf\n", main->calc->px, main->calc->py);
	mlx(main); //creates all mlx instances
	raycast(main); //game function
	//mlx_destroy_window
	//mlx_destroy_imgs
	//return_error(main, NONE)
	return (0);
}
