#include "../include/cub3D.h"

//use bilinear interpolation to resize pixels
//assume image is 64x64 pixels

/* 
1. find which slice of wall the ray is hitting (check for x column) 
2. find the wall height (pixel height)
3. divide wall height / upg to find scale of the wall
4. Throw into bilinear interpolate function
*/

int main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "textures/east.xpm";
	int		img_width;
	int		img_height;

	img_width = 0;
	img_height = 0;
	img = NULL;
	mlx = NULL;

	mlx = mlx_init();
	if (!mlx)
		printf("error\n");
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	if (!img)
		printf("error img\n");
	else
		printf("imgw: %i imgh: %i\n", img_width, img_height);
	mlx_loop(mlx);
}



