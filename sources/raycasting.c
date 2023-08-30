/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:56:51 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/30 22:44:51 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	cast_hline(t_calc *c, t_main *main)
{
	c->deltay = 0;
	c->deltax = 64;
	if (c->stepx == 1)
	{
		c->wall_face = main->img_we_wall;
		c->col_int = ceil(c->px / UPG) * UPG;
	}
	else if (c->stepx == -1)
	{
		c->wall_face = main->img_ea_wall;
		c->col_int = floor(c->px / UPG) * UPG;
	}
	c->col_inty = c->py;
	while (check_coord(COL, main))
		c->col_int += c->stepx * c->deltax;
	c->dist_col = c->px - c->col_int;
	c->cor_dist = fabs(c->dist_col * cos(c->rel_angle));
	c->wall_slice = (int)c->col_inty % 64;
}

void	cast_vline(t_calc *c, t_main *main)
{
	c->deltay = 64;
	c->deltax = 0;
	if (c->stepy == 1)
	{
		c->wall_face = main->img_no_wall;
		c->row_int = ceil(c->py / UPG) * UPG;
	}
	else if (c->stepy == -1)
	{
		c->wall_face = main->img_so_wall;
		c->row_int = floor(c->py / UPG) * UPG;
	}
	c->row_intx = c->px;
	while (check_coord(ROW, main))
		c->row_int += c->stepy * c->deltay;
	c->dist_row = c->py - c->row_int;
	c->cor_dist = fabs(c->dist_row * cos(c->rel_angle));
	c->wall_slice = (int)c->row_intx % 64;
}

void	calc_intercepts(t_calc *c, t_main *main)
{
	c->deltay = fabs(UPG * c->tan_angle);
	c->deltax = fabs(UPG / c->tan_angle);
	if (c->stepx == 1)
		c->col_int = ceil(c->px / UPG) * UPG;
	else if (c->stepx == -1)
		c->col_int = floor(c->px / UPG) * UPG;
	c->col_inty = c->py + (c->stepy 
			* fabs((c->col_int - c->px) * c->tan_angle));
	if (c->stepy == 1)
		c->row_int = ceil(c->py / UPG) * UPG;
	else if (c->stepy == -1)
		c->row_int = floor(c->py / UPG) * UPG;
	c->row_intx = c->px + (c->stepx
			* fabs((c->row_int - c->py) / c->tan_angle));
	while (check_coord(COL, main))
	{
		c->col_int += c->stepx * UPG;
		c->col_inty += c->stepy * c->deltay;
	}
	while (check_coord(ROW, main))
	{
		c->row_int += c->stepy * UPG;
		c->row_intx += c->stepx * c->deltax;
	}
}

void	cast_line(t_calc *c, t_main *main)
{
	calc_intercepts(c, main);
	c->dist_col = fabs((c->px - c->col_int) / cos(c->angle));
	c->dist_row = fabs((c->py - c->row_int) / sin(c->angle));
	if (c->dist_col <= c->dist_row)
	{
		c->wall_slice = (int)c->col_inty % 64;
		c->cor_dist = fabs(c->dist_col * cos(c->rel_angle));
		if (c->stepx == 1)
			c->wall_face = main->img_we_wall;
		else if (c->stepx == -1)
			c->wall_face = main->img_ea_wall;
	}
	else
	{
		c->wall_slice = (int)c->row_intx % 64;
		c->cor_dist = fabs(c->dist_row * cos(c->rel_angle));
		if (c->stepy == 1)
			c->wall_face = main->img_no_wall;
		else if (c->stepy == -1)
			c->wall_face = main->img_so_wall;
	}
}

void	raycast(t_main *main)
{
	t_calc	*c;
	int		x;

	c = main->calc;
	x = 0;
	draw_floor_ceiling(main);
	while (x < WIN_WIDTH)
	{
		if (ch_num(c->angle, 0) || ch_num(c->angle, M_PI))
			cast_hline(c, main);
		else if (ch_num(c->angle, c->rad_90) || ch_num(c->angle, c->rad_270))
			cast_vline(c, main);
		else
			cast_line(c, main);
		c->wall_height = c->height_ratio / c->cor_dist;
		draw_wall(x, main->calc, main);
		recalc_ray(main->calc);
		x++;
	}
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win,
		main->img.img, 0, 0);
}
