#include "../include/cub3D.h"

void	find_pix_color(t_pix *pix, t_main *main)
{
	int		offset;
	void	*addr;
	t_img	texture;

	texture = main->calc->wall_face;
	offset = pix->y * texture.line_length + pix->x * (texture.bpp / 8);
	addr = texture.addr + offset;

	// if (*((uint8_t *)addr) < 0)
	// 	pix->r = 256 + *((uint8_t *)addr);
	// else
	// if (*((uint8_t *)addr) < 0)
	// 	pix->g = 256 + *((uint8_t *)addr);
	// else
	// if (*((uint8_t *)addr) < 0)
	// 	pix->b = 256 + *((uint8_t *)addr);
	// else
	pix->r = *((uint8_t *)addr);
	addr++;
	pix->g = *((uint8_t *)addr);
	addr++;
	pix->b = *((uint8_t *)addr);
	// printf("r: %i g: %i b: %i\n", pix->r, pix->g, pix->b);
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
	*(unsigned int *)dst = avg_color;
}

void	draw_wall(int x, t_main *main)
{
	int		row;
	int		start;
	int		stop;
	t_point	p;
	
	row = 0;
	//note try floor/ceiling on this too
	start = (int)(round((main->calc->pln_height / 2) - (main->calc->wall_height / 2)));
	if (start < 0)
		start = 0;
	stop = (int)(round(start + main->calc->wall_height));
	if (stop >= main->calc->pln_height)
		stop = main->calc->pln_height - 1;
	p.scale = main->calc->wall_height / main->calc->upg;
	p.orig_x = main->calc->wall_slice;
	while (row < (int)main->calc->wall_height && start <= stop)
	{
		p.orig_y = row / p.scale;
		get_nearest_pix(&p, main);
		interpolate(x, start, &p, main);
		row++;
		start++;
	}

}