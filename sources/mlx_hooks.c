/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 16:06:42 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_close(t_main *main)
{
	mlx_destroy_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	return_error(main, NONE);
	exit(0);
}

int	rotate(int key, t_main *main)
{
	double	angle_rotation;
	t_calc	*c;

	c = main->calc;
	angle_rotation = ANGLE_ROT * (M_PI / 180);
	if (key == LEFT_KEY)
		angle_rotation *= -1;
	c->pdir += angle_rotation;
	if (c->pdir < 0)
		c->pdir += c->rad_360;
	else if (ch_num(c->pdir, c->rad_360) || c->pdir > c->rad_360)
		c->pdir -= c->rad_360;
	c->angle = c->pdir - (c->fov / 2);
	if (c->angle < 0)
		c->angle += c->rad_360;
	else if (ch_num(c->angle, c->rad_360) || c->angle > c->rad_360)
		c->angle -= c->rad_360;
	calc_step(main);
	calc_pdir_step(main);
	return (0);
}

//when pdir changes, reset angle calculations 
void	reset_pdir(t_main *main)
{
	t_calc	*c;

	c = main->calc;
	c->angle = c->pdir - (c->fov / 2);
	if (c->angle < 0)
		c->angle += c->rad_360;
	c->tan_angle = tan(c->angle);
	calc_step(main);
}

int	move(int key, t_main *main)
{
	reset_pdir(main);
	check_collision(key, main);
	raycast(main);
	return (0);
}

int	key_press(int key, t_main *main)
{
	if (key == ESC)
		ft_close(main);
	if (key == LEFT_KEY || key == RIGHT_KEY)
		rotate(key, main);
	else if (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY)
		move(key, main);
	else
		return (0);
	raycast(main);
	return (0);
}
