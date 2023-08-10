/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:19:55 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/11 01:11:55 by zsyyida          ###   ########.fr       */
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
	main->mlx.img_no = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/north.xpm", &size, &size);
	main->mlx.img_so = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/south.xpm", &size, &size);
	main->mlx.img_ea = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/east.xpm", &size, &size);
	main->mlx.img_we = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/west.xpm", &size, &size);
	main->mlx.img_spr1 = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/spr1.xpm", &size, &size);
	main->mlx.img_spr2 = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/spr2.xpm", &size, &size);
	main->mlx.img_door1 = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/door1.xpm", &size, &size);
	main->mlx.img_door2 = mlx_xpm_file_to_image(main->mlx.mlx_ptr,
			"./textures/door2.xpm", &size, &size);
}

//generate some textures
{
	unsigned long tw, th;
	loadImage(texture[0], tw, th, "textures/north.xpm");
	loadImage(texture[1], tw, th, "textures/south.xpm");
	loadImage(texture[2], tw, th, "textures/east.xpm");
	loadImage(texture[3], tw, th, "textures/west.xpm");
	loadImage(texture[4], tw, th, "textures/sprite.xpm");
	loadImage(texture[4], tw, th, "textures/door1.xpm");
	loadImage(texture[4], tw, th, "textures/door2.xpm");
}
