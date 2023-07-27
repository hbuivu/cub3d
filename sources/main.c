#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_main	*main;

	error_check(argc, argv);
	main = NULL;
	main = cub_calloc(1, sizeof(t_main), main);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("error\n not a file");
		return_error(main);
	}
	download_map(fd, main);
	print_omap(main->omap);
	parse_map(main->omap, main);
	print_main_map(main);
	return_error(main);
	// identify(str, map, argv, fd);
}
