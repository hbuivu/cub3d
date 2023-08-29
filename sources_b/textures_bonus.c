/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:58:42 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/28 00:12:40 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	get_textures_bonus(t_main *main)
{
	int	size;

	size = 200;
	main->texture = cub_calloc(9, sizeof(t_img), main);
	main->texture[0].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_0_.xpm", &size, &size);
	if (!main->texture[0].img)
		return_error(main, IMG_ERR);
	main->texture[1].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_1_.xpm", &size, &size);
	if (!main->texture[1].img)
		return_error(main, IMG_ERR);
	main->texture[2].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_2_.xpm", &size, &size);
	if (!main->texture[2].img)
		return_error(main, IMG_ERR);
	main->texture[3].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_3_.xpm", &size, &size);
	if (!main->texture[3].img)
		return_error(main, IMG_ERR);
	main->texture[4].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_4_.xpm", &size, &size);
	if (!main->texture[4].img)
		return_error(main, IMG_ERR);
		main->texture[5].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_5_.xpm", &size, &size);
	if (!main->texture[5].img)
		return_error(main, IMG_ERR);	
	main->texture[6].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_6_.xpm", &size, &size);
	if (!main->texture[6].img)
		return_error(main, IMG_ERR);
	main->texture[7].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_7_.xpm", &size, &size);
	if (!main->texture[7].img)
		return_error(main, IMG_ERR);
	main->texture[8].img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/texture_8_.xpm", &size, &size);
	if (!main->texture[8].img)
		return_error(main, IMG_ERR);
	get_data_addr_bonus(main);	
}

void	get_data_addr_bonus(t_main *main)
{
	main->texture[0].addr = mlx_get_data_addr(main->texture[0].img,
			&main->texture[0].bpp, &main->texture[0].line_length,
			&main->texture[0].endian);
	if (!main->texture[0].addr)
		return_error(main, IMG_ERR);
	main->texture[1].addr = mlx_get_data_addr(main->texture[1].img,
			&main->texture[1].bpp, &main->texture[1].line_length,
			&main->texture[1].endian);
	if (!main->texture[1].addr)
		return_error(main, IMG_ERR);
	main->texture[2].addr = mlx_get_data_addr(main->texture[2].img,
			&main->texture[2].bpp, &main->texture[2].line_length,
			&main->texture[2].endian);
	if (!main->texture[2].addr)
		return_error(main, IMG_ERR);
	main->texture[3].addr = mlx_get_data_addr(main->texture[3].img,
			&main->texture[3].bpp, &main->texture[3].line_length,
			&main->texture[3].endian);
	if (!main->texture[3].addr)
		return_error(main, IMG_ERR);
	main->texture[4].addr = mlx_get_data_addr(main->texture[4].img,
			&main->texture[4].bpp, &main->texture[4].line_length,
			&main->texture[4].endian);
	if (!main->texture[4].addr)
		return_error(main, IMG_ERR);
	main->texture[5].addr = mlx_get_data_addr(main->texture[5].img,
			&main->texture[5].bpp, &main->texture[5].line_length,
			&main->texture[5].endian);
	if (!main->texture[5].addr)
		return_error(main, IMG_ERR);
	main->texture[6].addr = mlx_get_data_addr(main->texture[6].img,
			&main->texture[6].bpp, &main->texture[6].line_length,
			&main->texture[6].endian);
	if (!main->texture[6].addr)
		return_error(main, IMG_ERR);
	main->texture[7].addr = mlx_get_data_addr(main->texture[7].img,
			&main->texture[7].bpp, &main->texture[7].line_length,
			&main->texture[7].endian);
	if (!main->texture[7].addr)
		return_error(main, IMG_ERR);
	main->texture[8].addr = mlx_get_data_addr(main->texture[8].img,
			&main->texture[8].bpp, &main->texture[8].line_length,
			&main->texture[8].endian);
	if (!main->texture[8].addr)
		return_error(main, IMG_ERR);
}