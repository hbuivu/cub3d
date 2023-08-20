#include "../include/cub3D.h"
#include <stdlib.h>

//use bilinear interpolation to resize pixels
//assume image is 64x64 pixels

/* 
1. find which slice of wall the ray is hitting (check for x column) 
2. find the wall height (pixel height)
3. divide wall height / upg to find scale of the wall
4. Throw into bilinear interpolate function lol
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

typedef struct s_pix
{
	int		x;
	int		y;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

}	t_pix;

typedef struct s_point
{
	double	or_w;
	double	or_h;
	int		new_w;
	int		new_h;
	double	orig_x; //how the point would translate on original image x axis
	double	orig_y; //how the point would transalte on original image y axis
	int		x1; //nearest point on x axis (round down origX)
	int		x2; //second nearest point on x axis (point next to x1)
	int		y1; //nearest point on y axis (round down origY)
	int		y2; //second nearest point on y axis (point next to y1)
	double	x_dist; //the distance of orig_x from x1
	double	y_dist; //the distance of orig_y from y1
	t_pix	*p1; //value of color at (y1, x1)
	t_pix	*p2; //value of color at (y1, x2)
	t_pix	*p3; //value of color at (y2, x1)
	t_pix	*p4; //value of color at (y2, x2)
}	t_point;

#define SCALE	5

void	find_pix_color(t_mlxz *mlx, t_pix *pix)
{
	int		offset;
	void	*addr;


	offset = pix->y * mlx->x_line_length + pix->x * (mlx->x_bpp / 8);
	addr = mlx->x_addr + offset;
	pix->r = *((uint32_t *)addr) >> 16;
	pix->g =  *((uint32_t *)addr) >> 8 & 255;
	pix->b = *((uint32_t *)addr) & 255;

	// pix->r = *((uint32_t *)addr) >> 16;
	// pix->g =  (*((uint32_t *)addr)- (pix->r << 16)) >> 8;
	// pix->b = (*((uint32_t *)addr) - (pix->r << 16) - (pix->g << 8));

	// pix->r = *((uint8_t *)addr);
	// addr++;
	// // if (*((uint8_t *)addr) < 0)
	// // 	pix->g = 256 + *((uint8_t *)addr);
	// // else
	// 	pix->g = *((uint8_t *)addr);
	// addr++;
	// // if (*((uint8_t *)addr) < 0)
	// // 	pix->b = 256 + *((uint8_t *)addr);
	// // else
	// 	pix->b = *((uint8_t *)addr);
	printf("r: %i g: %i b: %i\n", pix->r, pix->g, pix->b);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return (red << 16 | green << 8 | blue << 0);
}

void	resize_img(t_mlxz *mlx, int x, int y, t_point *p)
{
	int		offset;
	void	*dst;
	double	top_r;
	double	bottom_r;
	double	final_r;
	double	top_g;
	double	bottom_g;
	double	final_g;
	double	top_b;
	double	bottom_b;
	double	final_b;
	int		final_color;

	/* calculate r */
	top_r = ((p->p1->r * (1 - p->x_dist)) + (p->p2->r * p->x_dist));
	bottom_r = ((p->p3->r * (1 - p->x_dist)) + (p->p4->r * p->x_dist));
	final_r = ((top_r * (1 - p->y_dist)) + (bottom_r * p->y_dist));

	/* calculate g */
	top_g = ((p->p1->g * (1 - p->x_dist)) + (p->p2->g * p->x_dist));
	bottom_g = ((p->p3->g * (1 - p->x_dist)) + (p->p4->g * p->x_dist));
	final_g = ((top_g * (1 - p->y_dist)) + (bottom_g * p->y_dist));

	/* calculate b */
	top_b = ((p->p1->b * (1 - p->x_dist)) + (p->p2->b * p->x_dist));
	bottom_b = ((p->p3->b * (1 - p->x_dist)) + (p->p4->b * p->x_dist));
	final_b = ((top_b * (1 - p->y_dist)) + (bottom_b * p->y_dist));

	/* get final color and put in image */
	final_color = encode_rgb((int)final_r, (int)final_g, (int)final_b);
	offset = y * mlx->line_length + x * (mlx->bpp / 8);
	dst = mlx->addr + offset;
	*(unsigned int *)dst = final_color; 
}

int main(void)
{
	t_mlxz	*mlx;
	t_point	*p;
	char	*relative_path = "textures/spr1.xpm";

	mlx = NULL;
	p = NULL;
	mlx = calloc(1, sizeof(t_mlxz));
	p = calloc(1, sizeof(t_point));
	p->p1 = calloc(1, sizeof(t_pix));
	p->p2 = calloc(1, sizeof(t_pix));
	p->p3 = calloc(1, sizeof(t_pix));
	p->p4 = calloc(1, sizeof(t_pix));

	mlx->mlx_ptr = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, 500, 500, "test");

	mlx->x_img = mlx_xpm_file_to_image(mlx->mlx_ptr, relative_path, &mlx->x_imgw, &mlx->x_imgh);
	mlx->x_addr = mlx_get_data_addr(mlx->x_img, &mlx->x_bpp, &mlx->x_line_length, &mlx->x_endian);
	p->or_w = mlx->x_imgw;
	p->or_h = mlx->x_imgh;
	p->new_w = (int)(p->or_w * SCALE);
	p->new_h = (int)(p->or_h * SCALE);

	mlx->img = mlx_new_image(mlx->mlx_ptr, p->new_w, p->new_h);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_length, &mlx->endian);
		
	// printf("or_w: %lf\n", p->or_w);
	// printf("or_h: %lf\n", p->or_h);
	// printf("scale: %lf\n", SCALE);
	// printf("new_w: %i\n", p->new_w);
	// printf("new_h: %i\n", p->new_h);
	
	for (int row = 0; row < p->new_h; row++)
	{
		for (int col = 0; col < p->new_w; col++)
		{
			p->orig_x = col / SCALE;
			p->orig_y = row / SCALE;
			
			/* NOTE: check for boundaries here */
			p->x1 = (int)p->orig_x;
			p->x2 = p->x1 + 1;
			p->y1 = (int)p->orig_y;
			p->y2 = p->y1 + 1;

			/* establish x, y coordinates for each pixel and there must be a better way */
			p->p1->x = p->x1;
			p->p1->y = p->y1;
			p->p2->x = p->x1;
			p->p2->y = p->y2;
			p->p3->x = p->x1;
			p->p3->y = p->y1;
			p->p4->x = p->x1;
			p->p4->y = p->y1;
		
			/* fill out pixel information */
			find_pix_color(mlx, p->p1);
			find_pix_color(mlx, p->p2);
			find_pix_color(mlx, p->p3);
			find_pix_color(mlx, p->p4);

			p->x_dist = p->orig_x - p->x1;
			p->y_dist = p->orig_y - p->y1;
			
			// printf("col: %i row: %i\n", col, row);
			// printf("orig_x: %lf\n", p->orig_x);
			// printf("orig_y: %lf\n", p->orig_y);
			// printf("x1: %i\n", p->x1);
			// printf("x2: %i\n", p->x2);
			// printf("y1: %i\n", p->y1);
			// printf("y2: %i\n", p->y2);
			// printf("p1: %lf\n", p->p1);
			// printf("p2: %lf\n", p->p2);
			// printf("p3: %lf\n", p->p3);
			// printf("p4: %lf\n", p->p4);
			resize_img(mlx, col, row, p);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}

// int	limit = 64 * 64;
	// int i = 0;
	// while (i < limit - 4)
	// {
	// 	printf("r: %i g: %i b: %i a: %i\n", mlx->x_addr[i], mlx->addr[i + 1], mlx->x_addr[i + 2], mlx->x_addr[i + 3]);
	// 	i += 4;
	// }

// int	find_pixel_val(t_mlxz *m, int x, int y)
// {
// 	void	*dst;
// 	int		offset;
// 	int		color;

// 	offset = y * m->x_line_length + x * (m->x_bpp / 8);
// 	dst = m->x_addr + offset;
// 	color = *(unsigned int *)dst;
// 	return (color);
// }


