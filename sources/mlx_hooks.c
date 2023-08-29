/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/29 12:45:04 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_close(t_main *main)
{
	return_error(main, NONE);
	exit(0);
}

void	rotate(int key, t_calc *c)
{
	if (key == LEFT_KEY)
		c->pdir -= ANGLE_ROT;
	else if (key == RIGHT_KEY)
		c->pdir += ANGLE_ROT;
	if (c->pdir < 0)
		c->pdir += c->rad_360;
	else if (ch_num(c->pdir, c->rad_360) || c->pdir > c->rad_360)
		c->pdir -= c->rad_360;
	reset_ray(c);
}

void	calc_move(int key, t_calc *c)
{
	if (key == W_KEY)
		c->move_angle = c->pdir;
	else if (key == S_KEY)
		c->move_angle = c->pdir + M_PI;
	else if (key == A_KEY)
		c->move_angle = c->pdir - c->rad_90;
	else if (key == D_KEY)
		c->move_angle = c->pdir + c->rad_90;
	if (c->move_angle < 0)
		c->move_angle += c->rad_360;
	else if (ch_num(c->move_angle, c->rad_360) || c->move_angle > c->rad_360)
		c->move_angle -= c->rad_360;
	if (!ch_num(c->move_angle, c->rad_90) || !ch_num(c->move_angle, c->rad_270))
		c->tan_angle = tan(c->move_angle);
	calc_step(c->move_angle, c);
	c->x_walk = fabs(cos(c->move_angle)) * WALK * c->stepx;
	c->y_walk = fabs(sin(c->move_angle)) * WALK * c->stepy;
}

//returns 0 if player cannot move -> no raycasting required
int	move(int key, t_main *main)
{
	t_calc *c;
	double	wall_dist;
	double	new_move;

	c = main->calc;
	calc_move(key, c);
	if (ch_num(c->move_angle, 0) || ch_num(c->move_angle, M_PI))
		wall_dist = check_hline(c, main);
	else if (ch_num(c->move_angle, c->rad_90) || ch_num(c->move_angle, c->rad_270))
		wall_dist = check_vline(c, main);
	else
		wall_dist = check_line(c, main);
	if (wall_dist < WALK + WALL_BUFF)
	{
		new_move = wall_dist - WALL_BUFF;
		if (new_move < 0 || ch_num(new_move, 0))
			return (0);
		c->x_walk = fabs(cos(c->move_angle)) * new_move * c->stepx;
		c->y_walk = fabs(sin(c->move_angle)) * new_move * c->stepy;
	}
	c->px += c->x_walk;
	c->py += c->y_walk;
	reset_ray(main->calc);
	return (1);	
}

int	key_press(int key, t_main *main)
{
	if (key == ESC)
		ft_close(main);
	if (key == LEFT_KEY || key == RIGHT_KEY)
		rotate(key, main->calc);
	else if (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY)
	{
		if (move(key, main) == 0)
			return (0);	
	}
	else
		return (0);
	raycast(main);
	return (0);
}
