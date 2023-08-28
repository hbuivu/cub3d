/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:10:44 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/27 21:37:18 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calc_move(int key, t_calc *c)
{
	if (key == W_KEY)
	{
		c->x_walk = round(fabs(cos(c->pdir)) * WALK * c->pdir_stepx);
		c->y_walk = round(fabs(sin(c->pdir)) * WALK * c->pdir_stepy);
	}
	else if (key == S_KEY)
	{
		c->x_walk = round(fabs(cos(c->pdir)) * WALK * c->pdir_stepx * -1);
		c->y_walk = round(fabs(sin(c->pdir)) * WALK * c->pdir_stepy * -1);
	}
	else if (key == A_KEY)
	{
		c->x_walk = round(fabs(sin(c->pdir)) * WALK) * -1;
		c->y_walk = round(fabs(cos(c->pdir)) * WALK);
	}
	else if (key == D_KEY)
	{
		c->x_walk = round(fabs(sin(c->pdir)) * WALK);
		c->y_walk = round(fabs(cos(c->pdir)) * WALK) * -1;
	}
}

void	check_collision(int key, t_calc *c)
{
	double	new_px;
	double	new_py;

	calc_move(key, main);
	new_px = c->px + c->x_walk;
	new_py = c->py + c->y_walk;
	if (main->map[(int)(new_py / c->upg)][(int)((new_px + (WALL_BUFF * c->pdir_stepx)) / c->upg)] != '1' 
		&& main->map[(int)((new_py + (WALL_BUFF * c->pdir_stepy)) / c->upg)]
		[(int)(new_px / c->upg)] != '1')
	{
		c->px = new_px;
		c->py = new_py;
	}
}
