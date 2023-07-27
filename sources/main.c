#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_omap	*map;
	t_main	*main;

	error_check(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("error\n not a file");
		exit (1);
	}
	main = ft_calloc(sizeof(t_main), 1);
	if (!main)
	{
		perror("malloc error\n");
		exit(1);
	}
	map = NULL;
	download_map(fd, &map, main);
	print_omap(map);
	// identify(str, map, argv, fd);
}
