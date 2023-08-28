/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:22:23 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/28 16:46:28 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	parse_cub(int fd, t_main *main)
{
	t_omap	*begin_map;

	download_map(fd, main);
	begin_map = identify(main->omap, main);
	check_map(begin_map, main);
	get_map(begin_map, main); 

	check_walled(main);
}

//don't forget to destroy windows and images
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
	mlx(main);
	raycast(main);
	mlx_hook(main->mlx.mlx_win, 2, 1L << 0, key_press, main);
	mlx_hook(main->mlx.mlx_win, 17, 1L << 17, ft_close, main);
	mlx_loop(main->mlx.mlx_ptr);
	return_error(main, NONE);

	return (0);
}
