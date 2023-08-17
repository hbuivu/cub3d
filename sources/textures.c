/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 21:19:55 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/17 19:02:46 by zsyyida          ###   ########.fr       */
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

// char	**get_buffer(t_main *main, t_img img)
// {
// 	char 	*ptr;
// 	int		x;
// 	int		y;
// 	int		i;

// 	i = 0;
// 	ptr = img.addr;
// 	// while (i < (img.line_length) * (img.line_length))
// 	// {
// 	// 	printf("%i\n", ptr[i]);
// 	// 	i++;
// 	// }
// 	y = 0;
// 	img.buff = cub_calloc(img.line_length, sizeof(char *), main);
// 	while (y < img.line_length)
// 	{
// 		x = 0;
// 		while (x < img.line_length)
// 		{
// 			img.buff[y] = cub_calloc(img.line_length, sizeof(char), main);
// 			img.buff[y][x] = ptr[i];
// 			printf("img %i\n", ptr[i]);
// 			printf("buff %i\n", img.buff[y][x]);
// 			printf("i %i, x %x\n", i, x);
// 			x++;
// 			i++;
// 		}
// 		y++;
// 	}
// 	return (main->img.buff);
// }

void	get_textures(t_main *main)
{
	int size;
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
			main->e_path, &size, &size);
	if (!main->img_we_wall.img)
		return_error(main, IMG_ERR);
	get_data_addr(main);
}

/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
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
	// main->img_no_wall.buff = get_buffer(main, main->img_no_wall);
	// main->img_so_wall.buff = get_buffer(main, main->img_so_wall);
	// main->img_ea_wall.buff = get_buffer(main, main->img_ea_wall);
	// main->img_we_wall.buff = get_buffer(main, main->img_we_wall);
}

