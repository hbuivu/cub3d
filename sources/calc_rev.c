/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_rev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:31:03 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/26 18:33:40 by hbui-vu          ###   ########.fr       */
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

void	reset_rays(t_calc *c)
{
	c->angle = c->pdir - (c->fov / 2);
	if (c->angle < 0)
		c->angle += c->rad_360;
	c->tan_angle = tan(c->angle);
	calc_step(c->angle, c);
}

void	calc_player_angles(t_main *main)
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
	c->rad_90 = M_PI / 2;
	c->rad_270 = (3 * M_PI) / 2;
	c->rad_360 = M_PI * 2;
	c->upg = 64;
	c->fov = FOV * (M_PI / 180);
	c->pln_width = WIN_WIDTH;
	c->pln_height = WIN_HEIGHT;
	c->pln_dist = (c->pln_width / 2) / tan(c->fov / 2);
	c->ray_incr = c->fov / c->pln_width;


	
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
	calc_step(c->angle, main);
}
