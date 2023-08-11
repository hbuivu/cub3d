/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:19:55 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/11 16:41:37 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* dont pass actual width and height just an address for them
*to be stored in for mlx_xpm_file_to_image
Convert an xpm file to a new image instance.
void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename,
	int *width, int *height);
@param	void *mlx_ptr	the mlx instance;
@param	char *filename	the file to load;
@param	int  *width		a pointer to where the width ought to be written;
@param	int  *height	a pointer to where the height ought to be written;
since tile is a square can use same size for width and height
 @return	void*			the image instance, and NULL in case of error.
*/

void	get_textures(t_main *main)
{
	int	size;

	size = SIZE;
	main->img_no_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/north.xpm", &size, &size);
	if (!main->img_no_wall.img)
		return_error(main, MLX_ERR);
	main->img_so_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/south.xpm", &size, &size);
	if (!main->img_so_wall.img)
		return_error(main, MLX_ERR);
	main->img_ea_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/east.xpm", &size, &size);
	if (!main->img_ea_wall.img)
		return_error(main, MLX_ERR);
	main->img_we_wall.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/west.xpm", &size, &size);
	if (!main->img_we_wall.img)
		// return_error(main, MLX_ERR);
	// main->img_spr1.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			// "./textures/spr1.xpm", &size, &size);
	// if (!main->img_spr1.img)
		// return_error(main, MLX_ERR);
	// main->img_spr2.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			// "./textures/spr2.xpm", &size, &size);
	// if (!main->img_spr2.img)
		// return_error(main, MLX_ERR);
	// main->img_door1.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			// "./textures/door1.xpm", &size, &size);
	// if (!main->img_door1.img)
		// return_error(main, MLX_ERR);
	// main->img_door2.img = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			// "./textures/door2.xpm", &size, &size);
	// if (!main->img_door2.img)
		// return_error(main, MLX_ERR);
	get_data_addr(main);
}

/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
void	get_data_addr(t_main *main)
{
	main->img_no_wall.addr = mlx_get_data_addr(main->img_no_wall.img, &main->img_no_wall.bpp, &main->img_no_wall.line_length, &main->img_no_wall.endian);
	if (!main->img_no_wall.addr)
		return_error(main, MLX_ERR);
	main->img_so_wall.addr = mlx_get_data_addr(main->img_so_wall.img, &main->img_so_wall.bpp, &main->img_so_wall.line_length, &main->img_so_wall.endian);
	if (!main->img_so_wall.addr)
		return_error(main, MLX_ERR);
	main->img_ea_wall.addr = mlx_get_data_addr(main->img_ea_wall.img, &main->img_ea_wall.bpp, &main->img_ea_wall.line_length, &main->img_ea_wall.endian);
	if (!main->img_ea_wall.addr)
		return_error(main, MLX_ERR);
	main->img_we_wall.addr = mlx_get_data_addr(main->img_we_wall.img, &main->img_we_wall.bpp, &main->img_we_wall.line_length, &main->img_we_wall.endian);
	if (!main->img_we_wall.addr)
		return_error(main, MLX_ERR);
	//  main->img_spr1.addr = mlx_get_data_addr(main->img_spr1.img, &main->img_spr1.bpp, &main->img_spr1.line_length, &main->img_spr1.endian);
	//  if (!main->img_spr1.addr)
	 	// return_error(main, MLX_ERR);
	//  main->img_spr2.addr = mlx_get_data_addr(main->img_spr2.img, &main->img_spr2.bpp, &main->img_spr2.line_length, &main->img_spr2.endian);
	//  if (!main->img_spr2.addr)
	 	// return_error(main, MLX_ERR);
	//  main->img_door1.addr = mlx_get_data_addr(main->img_door1.img, &main->img_door1.bpp, &main->img_door1.line_length, &main->img_door1.endian);
	//  if (!main->img_door1.addr)
	 	// return_error(main, MLX_ERR);
	//  main->img_door2.addr = mlx_get_data_addr(main->img_door2.img, &main->img_door2.bpp, &main->img_door2.line_length, &main->img_door2.endian);
	//  if (!main->img_door2.addr)
	 	// return_error(main, MLX_ERR);
}

//generate some textures
// {
// 	unsigned long TW; 
// 	unsigned long TH;
	
// 	loadImage(texture[0], TW, TH, "textures/north.xpm");
// 	loadImage(texture[1], TW, TH, "textures/south.xpm");
// 	loadImage(texture[2], TW, TH, "textures/east.xpm");
// 	loadImage(texture[3], TW, TH, "textures/west.xpm");
// 	loadImage(texture[4], TW, TH, "textures/spr1.xpm");
//  loadImage(texture[4], TW, TH, "textures/spr2.xpm");
// 	loadImage(texture[4], TW, TH, "textures/door1.xpm");
// 	loadImage(texture[4], TW, TH, "textures/door2.xpm");
// }
