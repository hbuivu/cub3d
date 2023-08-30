/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:10:44 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/30 17:53:38 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double	check_hline(t_calc *c, t_main *main)
{
	double	wall_dist;

	c->deltay = 0;
	c->deltax = 64;
	if (c->stepx == 1)
		c->col_int = ceil(c->px / UPG) * UPG;
	else if (c->stepx == -1)
		c->col_int = floor(c->px / UPG) * UPG;
	c->col_inty = c->py;
	while (check_coord(COL, main))
		c->col_int += c->stepx * c->deltax;
	wall_dist = fabs(c->px - c->col_int);
	return (wall_dist);
}

double	check_vline(t_calc *c, t_main *main)
{
	double	wall_dist;

	c->deltay = 64;
	c->deltax = 0;
	if (c->stepy == 1)
		c->row_int = ceil(c->py / UPG) * UPG;
	else if (c->stepy == -1)
		c->row_int = floor(c->py / UPG) * UPG;
	c->row_intx = c->px;
	while (check_coord(ROW, main))
		c->row_int += c->stepy * c->deltay;
	wall_dist = fabs(c->py - c->row_int);
	return (wall_dist);
}

double	check_line(t_calc *c, t_main *main)
{
	double	wall_dist;

	calc_intercepts(c, main); //from raycasting function;
	c->dist_col = fabs((c->px - c->col_int) / cos(c->move_angle));
	c->dist_row = fabs((c->py - c->row_int) / sin(c->move_angle));
	if (c->dist_col <= c->dist_row)
		wall_dist = c->dist_col;
	else
		wall_dist = c->dist_row;
	return (wall_dist);
}
