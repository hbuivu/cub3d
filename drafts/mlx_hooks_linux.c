/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_linux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/23 23:24:55 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//do we need to destroy all images before closing

int	ft_close(t_main *main)
{
	return_error(main, NONE);
	mlx_destroy_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	exit(0);
}

int	key_press(int key_code, t_main *main)
{
	if (key_code == XK_Escape)
		ft_close(main);
	if (key_code == XK_Left)
	{
		main->calc->pdir -= 0.0349066; //2 degrees
		if (main->calc->pdir < 0)
			main->calc->pdir += main->calc->rad_360;
		main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
		if (main->calc->angle < 0)
			main->calc->angle += main->calc->rad_360;
		main->calc->tan_angle = tan(main->calc->angle);
		calc_step(main);
	}
	else if (key_code == XK_Right)
	{
		main->calc->pdir += 0.0349066; //2 degrees
		if (main->calc->pdir > main->calc->rad_360)
			main->calc->pdir -= main->calc->rad_360;
		main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
		if (main->calc->angle < 0)
			main->calc->angle += main->calc->rad_360;
		main->calc->tan_angle = tan(main->calc->angle);
		calc_step(main);
	}
	else if (key_code == XK_w)
	{
			// if (ch_num(fmod(main->calc->px, 64.0), 0))
			// 	if (!check_coord(COL, main))
			// 		break;
			// else if (ch_num(fmod(main->calc->py, 64.0), 0))
			// 	if (check_coord(ROW, main))
			// 		break;
			// main->calc->px += fabs(cos(main->calc->pdir)) * main->calc->stepx;
			// main->calc->py += fabs(sin(main->calc->pdir)) * main->calc->stepy;
			main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
			if (main->calc->angle < 0)
				main->calc->angle += main->calc->rad_360;
			else if (main->calc->angle > main->calc->rad_360 || ch_num(main->calc->angle, main->calc->rad_360))
				main->calc->angle -= main->calc->rad_360;
			main->calc->tan_angle = tan(main->calc->angle);
			main->calc->px++;
			main->calc->py++;	
	}
	else
		return (0);
	raycast(main);
    return (0);
}

	//check for every step if it takes you into a wall
	// else if (key_code == W_KEY) //NORTH
	// {
	// 	for (int i; i < 5; i++)
	// 	{
	// 		if (ch_num(fmod(main->calc->px, 64.0), 0))
	// 			if (!check_coord(COL, main))
	// 				break;
	// 		else if (ch_num(fmod(main->calc->py, 64.0), 0))
	// 			if (check_coord(ROW, main))
	// 				break;
	// 		main->calc->px += fabs(cos(main->calc->pdir)) * main->calc->stepx;
	// 		main->calc->py += fabs(sin(main->calc->pdir)) * main->calc->stepy;			
	// 	}
		
	// }
	// else if (key_code == S_KEY) //SOUTH
	// {
	// 	main->calc->px += cos(main->calc->pdir) * main->calc->stepx * -1;
	// 	main->calc->py += sin(main->calc->pdir) * main->calc->stepy * -1;
	// }
	// else if (key_code == D_KEY) //EAST
	// {
	// 	main->calc->px += sin(main->calc->pdir) * main->calc->stepx;
	// 	main->calc->py += cos(main->calc->pdir) * main->calc->stepy * -1;
	// }
	// else if (key_code == A_KEY) //WEST
	// {
	// 	main->calc->px += sin(main->calc->pdir) * main->calc->stepx * -1;
	// 	main->calc->py += cos(main->calc->pdir) * main->calc->stepy;
	// }