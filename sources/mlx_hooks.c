/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/22 14:41:02 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* change to print new image on top after updating x and y
	ft_printf("keycode = %d\n", key_code);
 do not use else if or game stops
*/

//do we need to destroy all images before closing
//need to implement wall collision and corner collision
// void	wall_collision(t_main *main)
// {
// 	//make sure to check for corner collision too
// 	//use a single ray to check, but ray does not need to be very long
// }
int	ft_close(t_main *main)
{
	mlx_destroy_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	// return_error(main, NONE);
	exit(0);
}

int	rotate(int key_code, t_main *main)
{
	double	angle_rotation;
	t_calc	*c;

	c = main->calc;
	angle_rotation = ANGLE_ROT * (M_PI / 180);
	if (key_code == LEFT_KEY)
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
	
}
//still need to implement wall collision
int	key_press(int key_code, t_main *main)
{
	if (key_code == ESC)
		ft_close(main);
	if (key_code == LEFT_KEY || key_code == RIGHT_KEY)
		rotate(key_code, main);
	else if (key_code == W_KEY || key_code == S_KEY || key_code == A_KEY || key_code == D_KEY)
		move(key_code, main);
	else
		return (0);
	raycast(main);
    return (0);
}

// int	move(int key_code, t_main *main)
// {
// 	c->angle = c->pdir - (c->fov / 2);
// 	if (c->angle < 0)
// 		c->angle += c->rad_360;
// 	else if (c->angle > c->rad_360 || ch_num(c->angle, c->rad_360))
// 		c->angle -= c->rad_360;
// 	c->tan_angle = tan(c->angle);
// 	calc_step(main);
// 	calc_pdir_step(main);
// 	if (key_code == W_KEY)
// 	{
// 		c->px += fabs(cos(c->pdir)) * c->pdir_stepx * WALK;
// 		c->py += fabs(sin(c->pdir)) * c->pdir_stepy * WALK;
// 		// printf("pdir: %lf\n", c->pdir);
// 		// printf("angle: %lf\n", c->angle);
// 		// printf("stepx: %i stepy: %i\n", c->stepx, c->stepy);
// 	}
// 	else if (key_code == S_KEY)
// 	{
// 		c->px += fabs(cos(c->pdir)) * c->pdir_stepx * -1 * WALK;
// 		c->py += fabs(sin(c->pdir)) * c->pdir_stepy * -1 * WALK;
// 	}
// 	else if (key_code == A_KEY)
// 	{
// 		c->px += fabs(sin(c->pdir)) * c->pdir_stepy * -1 * WALK;
// 		c->py += fabs(cos(c->pdir)) * c->pdir_stepx * WALK;
// 	}
// 	else if (key_code == D_KEY)
// 	{
// 		c->px += fabs(sin(c->pdir)) * c->pdir_stepy * WALK;
// 		c->py += fabs(cos(c->pdir)) * c->pdir_stepx * -1 * WALK;
// 	}
// 	return (0);
// }