/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 11:51:49 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/22 04:11:46 by zsyyida          ###   ########.fr       */
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

// int	*decode_rgb(int color, t_main *main)
// {
// 	int *rgb;

// 	rgb = cub_calloc(3, sizeof(int), main);
// 	rgb[0] = color >> 16;
// 	rgb[1] = color >> 8 & 255;
// 	rgb[2] = color & 255;
// 	return (rgb);
// }
// void	cub_miniview(t_game *g)
// {
// 	int	xy[2];
// 	int	aux[2];

// 	aux[1] = -1;
// 	xy[1] = (g->pl.y + 0.5) * SIZE - (int)(g->miniview.height / 2);
// 	while (++aux[1] < (g->miniview.height))
// 	{
// 		aux[0] = -1;
// 		xy[0] = (g->pl.x + 0.5) * SIZE - (int)(g->miniview.width / 2);
// 		while (++aux[0] < g->miniview.width)
// 		{
// 			if (xy[1] >= 0 && xy[1] < (g->height * SIZE) && xy[0] >= 0 \
// 						&& xy[0] < (g->width * SIZE))
// 				my_mlx_pixel_put(&g->miniview, aux[0], aux[1], \
// 					my_mlx_pixel_get(&g->minimap, xy[0], xy[1]));
// 			else
// 				my_mlx_pixel_put(&g->miniview, aux[0], aux[1], 0xFF000000);
// 			xy[0]++;
// 		}
// 		xy[1]++;
// 	}
// }

// void	cub_minimap(t_game *g)
// {
// 	int	xy[2];
// 	int	len;

// 	xy[1] = -1;
// 	while (++xy[1] < g->height)
// 	{
// 		xy[0] = -1;
// 		len = ft_strlen(g->map[xy[1]]);
// 		while (++xy[0] < g->width)
// 			my_mlx_area_put(&g->minimap, \
// 				ft_newvector(xy[0] * SIZE, xy[1] * SIZE), \
// 				ft_newvector(SIZE, SIZE), get_mini_color(g, len, xy));
// 	}
// }

// void	my_mlx_area_put(t_img *d, t_vector p, t_vector dim, int color)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < dim.y)
// 	{
// 		x = -1;
// 		while (++x < dim.x)
// 			my_mlx_pixel_put(d, p.x + x, p.y + y, color);
// 	}
// }


// int get_color_minimap(t_main *main, int row, int col)
// {
//     // printf("row %d col %d\n)", row, col);
// 	// printf(" \n%c\n", main->map[row][col]);
// 	if (main->map[row][col] == 'N' || main->map[row][col] == 'S' 
// 		|| main->map[row][col] == 'E' || main->map[row][col] == 'W')
// 		color = 255;
//     else if (main->map[row][col] == '2')
// 		color = 14924287;
//         // color = &(int){166,137, 225};
// 	else if (main->map[row][col] == '3')
// 		color = 14009505;
//         // color = &(int){229, 170, 112};
// 	else if (main->map[row][col] != '1')
// 		color = 15761536;
//         // color = &(int){240,128,128};
//      	// color = 4251856;
//         // color = &(int){64,224,205};
//     printf("color %i\n", color);
//     return (color);
// }

// void    draw_player_circle(t_main * main, int x, int y, int r)
// {
//     int     *color;
//     int     i;
//     int     angle;
//     int     x1;
//     int     y1;

//     color = cub_calloc(3, sizeof(int), main);
//     color[0] = 255;
//     color[1] = 36;
//     color[2] = 0;
//     i = 0;
//     while(i < 360)
//     {
//           angle = i;
//           x1 = r * cos(angle * M_PI / 180);
//           y1 = r * sin(angle * M_PI / 180);
//           ft_pixel_put(&main->img, x + x1, y + y1, rgb_to_int(color));
//           i = i + 0.1;
//     }
// }

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
			// ft_pixel_put(&main->img, col, row, 16777215);
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
