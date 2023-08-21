/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:13:40 by zsyyida           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/21 14:29:24 by hbui-vu          ###   ########.fr       */
=======
/*   Updated: 2023/08/17 14:47:03 by zsyyida          ###   ########.fr       */
>>>>>>> Zahra
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//ADD TEXTURES HERE



void	mlx(t_main *main)
{
	main->mlx.mlx_ptr = mlx_init();
	if (!main->mlx.mlx_ptr)
		return_error(main, MLX_ERR);
<<<<<<< HEAD
	main->mlx.mlx_win = mlx_new_window(main->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
=======
	get_textures(main);
	main->mlx.mlx_win = mlx_new_window(main->mlx.mlx_ptr, main->win_width, main->win_height, "Cub3D");
>>>>>>> Zahra
	if (!main->mlx.mlx_win)
		return_error(main, MLX_ERR);
	main->img.img = mlx_new_image(main->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!main->img.img)
		return_error(main, MLX_ERR);
	main->img.addr = mlx_get_data_addr(main->img.img, &main->img.bpp, &main->img.line_length, &main->img.endian);
	if (!main->img.addr)
		return_error(main, MLX_ERR);
	get_textures(main);
}
