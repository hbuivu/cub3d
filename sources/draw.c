#include "../include/cub3D.h"

void	find_pix_color(t_pix *pix, t_main *main)
{
	int		offset;
	void	*addr;
	t_img	texture;

	texture = main->calc->wall_face;
	offset = pix->y * texture.line_length + pix->x * (texture.bpp / 8);
	addr = texture.addr + offset;
	pix->r = *((uint32_t *)addr) >> 16;
	pix->g = *((uint32_t *)addr) >> 8 & 255;
	pix->b = *((uint32_t *)addr) & 255;
}

void	get_nearest_pix(t_point *p, t_main *main)
{
	p->p1.x = (int)p->orig_x;
	p->p1.y = (int)p->orig_y;
	p->p2.x = (int)p->orig_x;
	p->p2.y = (int)p->orig_y + 1;
	find_pix_color(&p->p1, main);
	find_pix_color(&p->p2, main);
	p->y_dist = p->orig_y - (int)p->orig_y;
}

void	interpolate(int x, int y, t_point *p, t_main *main)
{
	double	r;
	double	g;
	double	b;
	int		avg_color;
	int		offset;
	void	*dst;

	r = (p->p1.r * (1 - p->y_dist)) + (p->p2.r * p->y_dist);
	g = (p->p1.g * (1 - p->y_dist)) + (p->p2.g * p->y_dist);
	b = (p->p1.b * (1 - p->y_dist)) + (p->p2.b * p->y_dist);
	avg_color = encode_rgb((int)r, (int)g, (int)b);
	offset = y * main->img.line_length + x * (main->img.bpp / 8);
	dst = main->img.addr + offset;
	if (avg_color != 0) //if color is not black, print out pixel
		*(unsigned int *)dst = avg_color;
}

//note try floor/ceiling on this too
void	draw_wall(int x, t_main *main)
{
	int		row;
	int		start;
	int		stop;
	t_point	p;
	
	row = 0;
	start = (int)(round((main->calc->pln_height / 2) - (main->calc->wall_height / 2)));
	stop = (int)(round(start + main->calc->wall_height));
	if (stop >= main->calc->pln_height)
		stop = main->calc->pln_height - 1;
	p.scale = main->calc->wall_height / main->calc->upg;
	p.orig_x = main->calc->wall_slice;
	while (row < (int)main->calc->wall_height && start <= stop)
	{
		if (start >= 0)
		{
			p.orig_y = row / p.scale;
			get_nearest_pix(&p, main);
			interpolate(x, start, &p, main);
		}
		row++;
		start++;
	}
}

void	draw_floor_ceiling(t_main *main)
{
	int	row;
	int	col;
	int	*c;
	int	*f;

	row = -1;
	col = -1;
	c = main->c_color;
	f = main->f_color;
	while (++row < WIN_HEIGHT/2)
	{
		while (++col < WIN_WIDTH)
			ft_pixel_put(&main->img, col, row, encode_rgb(c[0], c[1], c[2]));
		col = -1;
	}
	col = -1;
	while (row < WIN_HEIGHT)
	{
		while (++col < WIN_WIDTH)
			ft_pixel_put(&main->img, col, row, encode_rgb(f[0], f[1], f[2]));
		col = -1;
		row++;
	}
}