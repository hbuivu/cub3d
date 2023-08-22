/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:51:49 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/22 04:18:41 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void    init_minimap(t_main *main)
{
    int size;

    size = 100;
    main->img_minimap.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/spr1.xpm", &size, &size);
    if (!main->img_minimap.img)
		return_error(main, IMG_ERR);
    main->img_minimap.addr = mlx_get_data_addr(main->img_minimap.img,
			&main->img_minimap.bpp, &main->img_minimap.line_length,
			&main->img_minimap.endian);
    if (!main->img_minimap.addr)
		return_error(main, MLX_ERR);
}

void	ft_pixel_tile_put(t_main *main, int col, int row, int color)
{
	int x;
	int y;

	y = 1;
	while (y < MM_TILE_SIZE - 1)
	{
		x = 1;
		while (x < MM_TILE_SIZE - 1)
		{
			ft_pixel_put(&main->img, col + x, row + y, color);
			x++;
		}
		y++;
	}
}

void    draw_minimap(t_main * main)
{
	int	row;
	int	col;

	row = 0;
	while (row < main->map_height)
	{
	    col = 0;
		while (col < main->map_width)
		{
			if (main->map[row][col] == '1')
				ft_pixel_tile_put(main, col * MM_TILE_SIZE, row * MM_TILE_SIZE, MM_WALL);
			else if (main->map[row][col] == '2')
				ft_pixel_tile_put(main, col * MM_TILE_SIZE, row * MM_TILE_SIZE, MM_SPRITE);
			else if (main->map[row][col] == '3')
				ft_pixel_tile_put(main, col * MM_TILE_SIZE, row * MM_TILE_SIZE, MM_DOOR);
			else if (main->map[row][col] == 'N' || main->map[row][col] == 'S' 
				|| main->map[row][col] == 'E' || main->map[row][col] == 'W')
				ft_pixel_tile_put(main, col * MM_TILE_SIZE, row * MM_TILE_SIZE, MM_PLAYER);
			col++;
	    }
		row++;
    }
}
