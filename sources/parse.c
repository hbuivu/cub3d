// #include "../include/cub3D.h"


// /*
// 1. Make sure F and C are there
// 2. Make sure NO, SO, WE, EA is there
// 3. After that, is the map
// */

// // int	main(int argc, char **argv)
// // {
// // 	t_game	game;
// // 	t_map	map;

// // 	map = (t_map){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL};
// // 	game = (t_game){NULL, NULL, NULL, NULL, NULL, NULL,
// // 		NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0};
// // 	error_check(argc, argv, map);
// // 	read_map(argv, &map);
// // 	init_game(&game, &map);
// // 	return (0);
// // }

// // int	ft_buff_size(char **argv)
// // {
// // 	int		i;
// // 	int		fd;
// // 	char	buff;

// // 	i = 0;
// // 	fd = open(argv[1], O_RDONLY);
// // 	if (fd == -1)
// // 	{
// // 		perror("error\n not a file");
// // 		exit (0);
// // 	}
// // 	while (read(fd, &buff, 1))
// // 		i++;
// // 	close(fd);
// // 	return (i);
// // }

// // void	read_map(char **argv, t_map	*map, int fd)
// // {
// // 	int		j;
// // 	char	buff;
// // 	int		str_size;
// // 	char	*str_map;

// // 	(void)map;
// // 	j = 0;
// // 	str_size = ft_buff_size(argv);

// // 	str_map = (char *) malloc(sizeof(char) * (str_size + 1));
// // 	if (!str_map)
// // 		return ;
// // 	while (read(fd, &buff, 1))
// // 	{
// // 		str_map[j++] = buff;
// // 	}
// // 	str_map[j] = '\0';
// // 	// map->str_map = str_map;
// // 	close(fd);
// // 	// error_check_helper(map);
// // }

// void	identify(char *str, t_map *map, char **argv, int fd)
// {
// 	while (str)
// 	{
// 		if (str[0] == 'F')
// 			map->f_color = str;
// 		if (str[0] == 'C')
// 			map->c_color = str;
// 		if (str[0] == 'N')
// 			map->n_path = str;
// 		if (str[0] == 'S')
// 			map->s_path = str;
// 		if (str[0] == 'E')
// 			map->e_path = str;
// 		if (str[0] == 'W')
// 			map->w_path = str;
// 		else if (str[0] == '1' || (str[0] == '0' && ft_strchr(str, '1') != NULL)
// 			|| (str[0] == ' ' && ft_strchr(str, '1') != NULL))
// 			read_map(argv, map, fd);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// }

