/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:31:03 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/30 14:50:30 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calc_step(double angle, t_calc *c)
{
	if (ch_num(angle, c->rad_90) || ch_num(angle, c->rad_270))
		c->stepx = 0;
	else if (angle < c->rad_90 || angle > c->rad_270)
		c->stepx = 1;
	else if (angle > c->rad_90 && angle < c->rad_270)
		c->stepx = -1;
	if (ch_num(angle, 0) || ch_num(angle, M_PI))
		c->stepy = 0;
	else if (angle > 0 && angle < M_PI)
		c->stepy = -1;
	else if (angle > M_PI && angle < c->rad_360)
		c->stepy = 1;
}

//note, we calculate tan_angle here because pdir starts in a straight direction
//therefore angle, will never be 0, 90, 180, 270
void	calc_player_info(t_main *main)
{
	t_calc *c;

	c = main->calc;
	c->px = ((main->player_pos[0] + .5) * UPG);
	c->py = ((main->player_pos[1] + .5) * UPG);
	if (main->player_dir == 'E')
		c->pdir = 0;
	else if (main->player_dir == 'N')
		c->pdir = c->rad_90;
	else if (main->player_dir == 'W')
		c->pdir = M_PI;
	else if (main->player_dir == 'S')
		c->pdir = c->rad_270;
	c->rel_angle = c->fov / 2;
	c->angle = c->pdir - c->rel_angle;
	if (c->angle < 0)
		c->angle += c->rad_360;
	c->tan_angle = tan(c->angle);
	calc_step(c->angle, c);
}

void	init_calc(t_main *main)
{
	t_calc	*c;

	main->calc = (t_calc *)cub_calloc(1, sizeof(t_calc), main);
	c = main->calc;
	c->rad_90 = M_PI / 2;
	c->rad_270 = (3 * M_PI) / 2;
	c->rad_360 = M_PI * 2;
	c->fov = FOV * (M_PI / 180);
	c->midpt = WIN_HEIGHT / 2;
	c->pln_dist = (WIN_WIDTH / 2) / tan(c->fov / 2);
	c->height_ratio = TH * c->pln_dist;
	c->ray_incr = c->fov / WIN_WIDTH;
	calc_player_info(main);
}

void	reset_ray(t_calc *c)
{
	c->rel_angle = c->fov / 2;
	c->angle = c->pdir - c->rel_angle;
	if (c->angle < 0)
		c->angle += c->rad_360;
	if (!ch_num(c->angle, c->rad_90) && !ch_num(c->angle, c->rad_270))
		c->tan_angle = tan(c->angle);
	calc_step(c->angle, c);
}

void	recalc_ray(t_calc *c)
{
	c->angle += c->ray_incr;
	if (c->angle > c->rad_360 || ch_num(c->angle, c->rad_360))
		c->angle -= c->rad_360;
	c->rel_angle -= c->ray_incr;
	if (!ch_num(c->angle, c->rad_90) && !ch_num(c->angle, c->rad_270))
		c->tan_angle = tan(c->angle);
	calc_step(c->angle, c);
}

// void	reset_vars(t_calc *c)
// {
// 	c->col_int = 0;
// 	c->col_inty = 0;
// 	c->row_int = 0;
// 	c->row_intx = 0;
// 	c->deltax = 0;
// 	c->deltay = 0;
// 	c->dist_col = 0;
// 	c->dist_row = 0;
// 	c->cor_dist = 0;
// 	c->wall_height = 0;
// 	c->wall_face = NULL;
// 	c->wall_slice = 0;
// }
