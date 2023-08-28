/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:31:03 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/27 23:48:31 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calc_pdir_step(t_main *main)
{
	t_calc	*c;

	c = main->calc;
	if (ch_num(c->pdir, c->rad_90) || ch_num(c->pdir, c->rad_270))
		c->pdir_stepx = 0;
	else if (c->pdir < c->rad_90 || c->pdir > c->rad_270)
		c->pdir_stepx = 1;
	else if (c->pdir > c->rad_90 && c->pdir < c->rad_270)
		c->pdir_stepx = -1;
	if (ch_num(c->pdir, 0) || ch_num(c->pdir, M_PI))
		c->pdir_stepy = 0;
	else if (c->pdir > 0 && c->pdir < M_PI)
		c->pdir_stepy = -1;
	else if (c->pdir > M_PI && c->pdir < c->rad_360)
		c->pdir_stepy = 1;
}

void	calc_step(t_main *main)
{
	t_calc	*c;

	c = main->calc;
	if (ch_num(c->angle, c->rad_90) || ch_num(c->angle, c->rad_270))
		c->stepx = 0;
	else if (c->angle < c->rad_90 || c->angle > c->rad_270)
		c->stepx = 1;
	else if (c->angle > c->rad_90 && c->angle < c->rad_270)
		c->stepx = -1;
	if (ch_num(c->angle, 0) || ch_num(c->angle, M_PI))
		c->stepy = 0;
	else if (c->angle > 0 && c->angle < M_PI)
		c->stepy = -1;
	else if (c->angle > M_PI && c->angle < c->rad_360)
		c->stepy = 1;
}

void	calc_rad(t_main *main)
{
	main->calc->rad_90 = M_PI / 2;
	main->calc->rad_270 = (3 * M_PI) / 2;
	main->calc->rad_360 = M_PI * 2;
}

void	calc_pdir(t_main *main)
{
	t_calc	*c;

	c = main->calc;
	if (main->player_dir == 'E')
		c->pdir = 0;
	else if (main->player_dir == 'N')
		c->pdir = c->rad_90;
	else if (main->player_dir == 'W')
		c->pdir = M_PI;
	else if (main->player_dir == 'S')
		c->pdir = c->rad_270;
}

void	init_calc(t_main *main)
{
	t_calc	*c;

	main->calc = (t_calc *)cub_calloc(1, sizeof(t_calc), main);
	c = main->calc;
	calc_rad(main);
	c->upg = 64;
	c->fov = FOV * (M_PI / 180);
	c->pln_width = WIN_WIDTH;
	c->pln_height = WIN_HEIGHT;
	c->pln_dist = (c->pln_width / 2) / tan(c->fov / 2);
	c->px = ((main->player_pos[0] + .5) * c->upg);
	c->py = ((main->player_pos[1] + .5) * c->upg);
	calc_pdir(main);
	c->angle = c->pdir - (c->fov / 2);
	if (c->angle < 0)
		c->angle += c->rad_360;
	else if (c->angle > c->rad_360 || ch_num(c->angle, c->rad_360))
		c->angle -= c->rad_360;
	c->tan_angle = tan(c->angle);
	c->tan_pdir = tan(c->pdir);
	c->ray_incr = c->fov / c->pln_width;
	calc_step(main);
	calc_pdir_step(main);
}

void	recalc(t_main *main)
{
	t_calc	*c;

	c = main->calc;
	c->angle += c->ray_incr;
	if (c->angle < 0)
		c->angle += c->rad_360;
	else if (c->angle > c->rad_360 || ch_num(c->angle, c->rad_360))
		c->angle -= c->rad_360;
	c->tan_angle = tan(c->angle);
	calc_step(main);
}
