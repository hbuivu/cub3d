/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:51:49 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/23 18:12:57 by zsyyida          ###   ########.fr       */
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
	int	player[2];
	// int	row_player;
	// int col_player;

	row = 0;
	player[1] = (main->calc->py + .5) * MM_TILE_SIZE ;
	while (row < main->map_height)
	{
		// row_player = (int)abs((int)main->calc->py / MM_TILE_SIZE * MM_TILE_SIZE) * -1;
		// col_player = (int)abs((int)main->calc->px / MM_TILE_SIZE * MM_TILE_SIZE) * -1;
	    col = 0;
		player[0] = (main->calc->px + .5) * MM_TILE_SIZE ;
		if (main->map_height > 30 || main->map_width > 30)
			return ;
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
			// else if (row == row_player && col == col_player))
				ft_pixel_tile_put(main, col * MM_TILE_SIZE, row * MM_TILE_SIZE, MM_PLAYER);
			else
				ft_pixel_tile_put(main, col * MM_TILE_SIZE, row * MM_TILE_SIZE, MM_FLOOR);
			col++;
	    }
		row++;
    }
}
