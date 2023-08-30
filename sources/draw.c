/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:43:26 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/30 18:00:37 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	draw_wall(int x, t_calc *c, t_main *main)
{
	int		row;
	int		start;
	int		stop;
	t_point	p;

	row = 0;
	start = (int)(round((c->midpt) - (c->wall_height / 2)));
	stop = (int)(round(start + c->wall_height));
	if (stop >= WIN_HEIGHT)
		stop = WIN_HEIGHT - 1;
	p.scale = c->wall_height / TH;
	p.orig_x = c->wall_slice;
	while (row < (int)c->wall_height && start <= stop)
	{
		if (start >= 0)
		{
			p.orig_y = row / p.scale;
			if (p.orig_y > (double)TH - 1)
				p.orig_y = (double)TH - 1;
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
	while (++row < WIN_HEIGHT / 2)
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
