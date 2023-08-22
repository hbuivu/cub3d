/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_imgs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:37:46 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/21 23:45:57 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	get_textures(t_main *main)
{
	int	size;

	size = 200;
	main->img_no_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			main->n_path, &size, &size);
	if (main->img_no_wall.img == NULL)
		return_error(main, IMG_ERR);
	main->img_so_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			main->s_path, &size, &size);
	if (!main->img_so_wall.img)
		return_error(main, IMG_ERR);
	main->img_ea_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			main->e_path, &size, &size);
	if (!main->img_ea_wall.img)
		return_error(main, IMG_ERR);
	main->img_we_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			main->w_path, &size, &size);
	if (!main->img_we_wall.img)
		return_error(main, IMG_ERR);
	get_data_addr(main);
}

void	get_data_addr(t_main *main)
{
	main->img_no_wall.addr = mlx_get_data_addr(main->img_no_wall.img,
			&main->img_no_wall.bpp, &main->img_no_wall.line_length,
			&main->img_no_wall.endian);
	if (!main->img_no_wall.addr)
		return_error(main, IMG_ERR);
	main->img_so_wall.addr = mlx_get_data_addr(main->img_so_wall.img,
			&main->img_so_wall.bpp, &main->img_so_wall.line_length,
			&main->img_so_wall.endian);
	if (!main->img_so_wall.addr)
		return_error(main, MLX_ERR);
	main->img_ea_wall.addr = mlx_get_data_addr(main->img_ea_wall.img,
			&main->img_ea_wall.bpp, &main->img_ea_wall.line_length,
			&main->img_ea_wall.endian);
	if (!main->img_ea_wall.addr)
		return_error(main, MLX_ERR);
	main->img_we_wall.addr = mlx_get_data_addr(main->img_we_wall.img,
			&main->img_we_wall.bpp, &main->img_we_wall.line_length,
			&main->img_we_wall.endian);
	if (!main->img_we_wall.addr)
		return_error(main, MLX_ERR);
	get_textures_bonus(main);
}


void	mlx(t_main *main)
{
	main->mlx.mlx_ptr = mlx_init();
	if (!main->mlx.mlx_ptr)
		return_error(main, MLX_ERR);
	main->mlx.mlx_win = mlx_new_window(main->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
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
