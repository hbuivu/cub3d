/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/22 12:44:38 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* change to print new image on top after updating x and y
	ft_printf("keycode = %d\n", key_code);
 do not use else if or game stops
*/

//do we need to destroy all images before closing
//need to implement wall collision
//issue with rotation and moving forward, check that angles are being added correctly

int	ft_close(t_main *main)
{
	mlx_destroy_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	// return_error(main, NONE);
	exit(0);
}

int	move(int key_code, t_main *main)
{
	main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
	if (main->calc->angle < 0)
		main->calc->angle += main->calc->rad_360;
	else if (main->calc->angle > main->calc->rad_360 || ch_num(main->calc->angle, main->calc->rad_360))
		main->calc->angle -= main->calc->rad_360;
	main->calc->tan_angle = tan(main->calc->angle);
	if (key_code == W_KEY)
	{
		main->calc->px += fabs(cos(main->calc->pdir)) * main->calc->stepx * WALK;
		main->calc->py += fabs(sin(main->calc->pdir)) * main->calc->stepy * WALK;
	}
	else if (key_code == S_KEY)
	{
		main->calc->px += fabs(cos(main->calc->pdir)) * main->calc->stepx * -1 * WALK;
		main->calc->py += fabs(sin(main->calc->pdir)) * main->calc->stepy * -1 * WALK;
	}
	else if (key_code == A_KEY)
	{
		main->calc->px += fabs(sin(main->calc->pdir)) * main->calc->stepy * -1 * WALK;
		main->calc->py += fabs(cos(main->calc->pdir)) * main->calc->stepx * WALK;
	}
	else if (key_code == D_KEY)
	{
		main->calc->px += fabs(sin(main->calc->pdir)) * main->calc->stepy * WALK;
		main->calc->py += fabs(cos(main->calc->pdir)) * main->calc->stepx * -1 * WALK;
	}
	return (0);
}

//still need to implement wall collision
int	key_press(int key_code, t_main *main)
{
	if (key_code == ESC)
		ft_close(main);
	if (key_code == LEFT_KEY)
	{
		main->calc->pdir -= 0.0349066; //2 degrees
		if (main->calc->pdir < 0)
			main->calc->pdir += main->calc->rad_360;
		main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
		if (main->calc->angle < 0)
			main->calc->angle += main->calc->rad_360;
		calc_step(main);
		// printf("pdir: %lf\n", main->calc->pdir);
		// printf("angle: %lf\n", main->calc->angle);
		// printf("stepx: %i stepy: %i\n", main->calc->stepx, main->calc->stepy);
	}
	else if (key_code == RIGHT_KEY)
	{
		main->calc->pdir += 0.0349066; //2 degrees
		if (ch_num(main->calc->pdir, main->calc->rad_360) || main->calc->pdir > main->calc->rad_360)
			main->calc->pdir -= main->calc->rad_360;
		main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
		if (main->calc->angle < 0)
			main->calc->angle += main->calc->rad_360;
		calc_step(main);
		// printf("pdir: %lf\n", main->calc->pdir);
		// printf("angle: %lf\n", main->calc->angle);
		// printf("stepx: %i stepy: %i\n", main->calc->stepx, main->calc->stepy);
	}
	else if (key_code == W_KEY || key_code == S_KEY || key_code == A_KEY || key_code == D_KEY)
		move(key_code, main);
	else
		return (0);
	raycast(main);
    return (0);
}