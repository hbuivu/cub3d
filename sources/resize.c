#include "../include/cub3D.h"
#include <stdlib.h>

//use bilinear interpolation to resize pixels
//assume image is 64x64 pixels

/* 
1. find which slice of wall the ray is hitting (check for x column) 
2. find the wall height (pixel height)
3. divide wall height / upg to find scale of the wall
4. Throw into bilinear interpolate function
*/

typedef struct	s_mlxz
{
	void	*x_img;
	int		x_imgw;
	int		x_imgh;
	char	*x_addr;
	int		x_bpp;
	int		x_line_length;
	int		x_endian;

	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlxz;

typedef struct s_point
{
	double	or_w;
	double	or_h;
	double	new_w;
	double	new_h;
	double	orig_x; //how the point would translate on original image x axis
	double	orig_y; //how the point would transalte on original image y axis
	int		x1; //nearest point on x axis (round down origX)
	int		x2; //second nearest point on x axis (point next to x1)
	int		y1; //nearest point on y axis (round down origY)
	int		y2; //second nearest point on y axis (point next to y1)
	double	x_dist; //the distance of orig_x from x1
	double	y_dist; //the distance of orig_y from y1
	double	v1; //value of color at (y1, x1)
	double	v2; //value of color at (y1, x2)
	double	v3; //value of color at (y2, x1)
	double	v4; //value of color at (y2, x2)
}	t_point;

#define SCALE	1.7

int	find_pixel_val(t_mlxz *m, int x, int y)
{
	void	*dst;
	int		offset;
	int		color;

	offset = y * m->x_line_length + x * (m->x_bpp / 8);
	dst = m->x_addr + offset;
	color = *(unsigned int *)dst;
	return (color);
}

void	resize_img(t_mlxz *m, int x, int y, t_point *p)
{
	double	top;
	double	bottom;
	double	final_color;
	void	*dst;
	int		offset;
	int		color;

	top = (p->v1 * (1 - p->x_dist)) + (p->v2 * p->x_dist);
	bottom = (p->v3 * (1 - p->x_dist)) + (p->v4 * p->x_dist);
	final_color = (top * (1 - p->y_dist)) + (bottom * p->y_dist);
	color = (int)final_color;
	offset = y * m->line_length + x * (m->bpp / 8);
	dst = m->addr + offset;
	*(unsigned int *)dst = color; 
}

int main(void)
{
	t_mlxz	*mlx;
	t_point	*p;
	char	*relative_path = "textures/east.xpm";

	(void) mlx;
	(void) p;
	(void) relative_path;


	mlx = calloc(1, sizeof(t_mlx));
	p = calloc(1, sizeof(t_point));
	mlx->mlx_ptr = mlx_init();
	mlx->x_img = mlx_xpm_file_to_image(mlx->mlx_ptr, relative_path, &mlx->x_imgw, &mlx->x_imgh);
	mlx->x_addr = mlx_get_data_addr(mlx->x_img, &mlx->x_bpp, &mlx->x_line_length, &mlx->x_endian);
	// printf("value: %i\n", find_pixel_val(mlx, 0, 0));

	p->or_w = mlx->x_imgw;
	p->or_h = mlx->x_imgh;
	p->new_w = p->or_w * SCALE;
	p->new_h = p->or_h * SCALE;
	mlx->img = mlx_new_image(mlx->mlx_ptr, p->new_w, p->new_h);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_length, &mlx->endian);
	
	printf("or_w: %lf\n", p->or_w);
	printf("or_h: %lf\n", p->or_h);
	printf("scale: %lf\n", SCALE);
	printf("new_w: %lf\n", p->new_w);
	printf("new_h: %lf\n", p->new_h);

	// for (int row = 0; row < p->new_h; row++)
	// {
	// 	for (int col = 0; col < p->new_w; col++)
	// 	{
	// 		p->orig_x = (double)col / SCALE;
	// 		p->orig_y = (double)row / SCALE;

	// 		//check for boundaries here
	// 		p->x1 = (int)p->orig_x;
	// 		p->x2 = p->x1 + 1;
	// 		p->y1 = (int)p->orig_y;
	// 		p->y2 = p->y1 + 1;

	// 		p->v1 = find_pixel_val(mlx, p->x1, p->y1);
	// 		p->v2 = find_pixel_val(mlx, p->x1, p->y2);
	// 		p->v3 = find_pixel_val(mlx, p->x2, p->v1);
	// 		p->v4 = find_pixel_val(mlx, p->x2, p->y2);

	// 		p->x_dist = p->orig_x - p->x1;
	// 		p->y_dist = p->orig_y - p->y1;
			
	// 		printf("col: %i row: %i\n", col, row);
	// 		printf("orig_x: %lf\n", p->orig_x);
	// 		printf("orig_y: %lf\n", p->orig_y);
	// 		printf("x1: %i\n", p->x1);
	// 		printf("x2: %i\n", p->x2);
	// 		printf("y1: %i\n", p->y1);
	// 		printf("y2: %i\n", p->y2);
	// 		printf("v1: %lf\n", p->v1);
	// 		printf("v2: %lf\n", p->v2);
	// 		printf("v3: %lf\n", p->v3);
	// 		printf("v4: %lf\n", p->v4);
	// 		// resize_img(mlx, col, row, p);
	// 	}
	// }
	// mlx_loop(mlx);
}



