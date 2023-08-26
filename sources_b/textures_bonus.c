/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:58:42 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 13:02:47 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	get_textures_bonus(t_main *main)
{
	// t_texture	texture[8];
	int	size;

	size = 200;
	// texture = (t_texture *)cub_calloc(8, sizeof(t_texture), main);
	main->img_spr1.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/spr1.xpm", &size, &size);
	if (!main->img_spr1.img)
		return_error(main, IMG_ERR);
	main->img_spr2.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/spr2.xpm", &size, &size);
	if (!main->img_spr2.img)
		return_error(main, IMG_ERR);
	main->img_door1.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/door1.xpm", &size, &size);
	if (!main->img_door1.img)
		return_error(main, IMG_ERR);
	// main->img_door2.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
	// 		"./textures/door2.xpm", &size, &size);
	// if (!main->img_door2.img)
	// 	return_error(main, IMG_ERR);
	get_data_addr_bonus(main);
}

/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
void	get_data_addr_bonus(t_main *main)
{
	main->img_spr1.addr = mlx_get_data_addr(main->img_spr1.img,
			&main->img_spr1.bpp, &main->img_spr1.line_length,
			&main->img_spr1.endian);
	if (!main->img_spr1.addr)
		return_error(main, MLX_ERR);
	main->img_spr2.addr = mlx_get_data_addr(main->img_spr2.img,
			&main->img_spr2.bpp, &main->img_spr2.line_length,
			&main->img_spr2.endian);
	if (!main->img_spr2.addr)
		return_error(main, MLX_ERR);
	main->img_door1.addr = mlx_get_data_addr(main->img_door1.img,
			&main->img_door1.bpp, &main->img_door1.line_length,
			&main->img_door1.endian);
	if (!main->img_door1.addr)
		return_error(main, MLX_ERR);
	// main->img_door2.addr = mlx_get_data_addr(main->img_door2.img,
	// 		&main->img_door2.bpp, &main->img_door2.line_length,
	// 		&main->img_door2.endian);
	// if (!main->img_door2.addr)
	// 	return_error(main, MLX_ERR);
}