#include "cub3D.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * img->line_length + x * (img->bpp / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

//what about alpha channel
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    return (red << 24 | green << 15 | blue << 8 | alpha);
}

// void	draw_floor_ceiling(t_main *main)
// {
// 	int	row;
// 	int	col;

// 	row = 0;
// 	col = 0;
// 	// draw ceiling (top half of window)
// 	// printf("h:%i w:%i\n", main->win_height, main->win_width);
// 	while (row < main->win_height/2)
// 	{
// 		// printf("row=%i\n", row);
// 		while (col < main->win_width)
// 		{
// 			// printf("col=%i\n", col);
// 			ft_pixel_put(main->img, col, row, encode_rgb(255, 0, 0, 100));
// 			col++;
// 		}
// 		col = 0;
// 		row++;
// 	}
// 	while (row < main->win_height)
// 	{
// 		while (col < main->win_width)
// 		{
// 			ft_pixel_put(main->img, col, row, encode_rgb(255, 0, 0, 120));
// 			col++;
// 		}
// 		col = 0;
// 		row++;
// 	}
// 	mlx_put_image_to_window(main->mlx->mlx_ptr, main->mlx->mlx_win, main->img->img, 0, 0);
// }

// void	draw_walls(t_main *main)
// {
	
// }

void	mlx(t_main *main)
{
	main->mlx.mlx_ptr = mlx_init();
	if (!main->mlx.mlx_ptr)
		return_error(main, MLX_ERR);
	main->mlx.mlx_win = mlx_new_window(main->mlx.mlx_ptr, main->win_width, main->win_height, "Cub3D");
	if (!main->mlx.mlx_win)
		return_error(main, MLX_ERR);
	main->img.img = mlx_new_image(main->mlx.mlx_ptr, main->win_width, main->win_height);
	if (!main->img.img)
		return_error(main, MLX_ERR);
	main->img.addr = mlx_get_data_addr(main->img.img, &main->img.bpp, &main->img.line_length, &main->img.endian);
	if (!main->img.addr)
		return_error(main, MLX_ERR);
	// raycast(main);
	// mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
	// draw_floor_ceiling(main);
	// mlx_key_hook(main->mlx.mlx_win, ft_movement, main);
	mlx_hook(main->mlx.mlx_win, 17, 1L << 17, ft_close, main);
	// mlx_loop(main->mlx.mlx_ptr);
	
}
