/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:13:40 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/19 16:25:37 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * img->line_length + x * (img->bpp / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	mlx(t_main *main)
{
	main->mlx.mlx_ptr = mlx_init();
	if (!main->mlx.mlx_ptr)
		return_error(main, MLX_ERR);
	get_textures(main);
	main->mlx.mlx_win = mlx_new_window(main->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!main->mlx.mlx_win)
		return_error(main, MLX_ERR);
	main->img.img = mlx_new_image(main->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!main->img.img)
		return_error(main, MLX_ERR);
	main->img.addr = mlx_get_data_addr(main->img.img, &main->img.bpp, &main->img.line_length, &main->img.endian);
	if (!main->img.addr)
		return_error(main, MLX_ERR);
	mlx_hook(main->mlx.mlx_win, 17, 1L<<17, ft_close, &main->mlx);
	mlx_hook(main->mlx.mlx_win, 2, 1L<<0, key_press, &main->mlx);
	// raycast(main);
	// mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
	// mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img_no_wall.img, 0, 0)

}
