/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:11:15 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/28 13:34:05 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//what about alpha channel
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * img->line_length + x * (img->bpp / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

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
	int		offset;
	void	*dst;

	get_nearest_pix(p, main);
	r = (p->p1.r * (1 - p->y_dist)) + (p->p2.r * p->y_dist);
	g = (p->p1.g * (1 - p->y_dist)) + (p->p2.g * p->y_dist);
	b = (p->p1.b * (1 - p->y_dist)) + (p->p2.b * p->y_dist);
	offset = y * main->img.line_length + x * (main->img.bpp / 8);
	dst = main->img.addr + offset;
	*(unsigned int *)dst = encode_rgb((int)r, (int)g, (int)b);
}