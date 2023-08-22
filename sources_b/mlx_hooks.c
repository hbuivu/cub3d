/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/22 02:54:39 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* change to print new image on top after updating x and y
	ft_printf("keycode = %d\n", key_code);
 do not use else if or game stops
*/

//do we need to destroy all images before closing

int	mouse_move(int x, int y, t_main *main)
{
	if (y != -1)
		main->calc->angle += (x - main->mouse_x) / 3;
	main->mouse_x = x;
	return (0);
}

int	ft_close(t_main *main)
{
	mlx_destroy_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	// return_error(main, NONE);
	exit(0);
}

// Mouse code for MacOS:
// Left click: 1
// Right click: 2
// Middle click: 3
// Scroll up: 4
// Scroll down : 5
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
	}
	else if (key_code == RIGHT_KEY)
	{
		main->calc->pdir += 0.0349066; //2 degrees
		if (main->calc->pdir > main->calc->rad_360)
			main->calc->pdir -= main->calc->rad_360;
		main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
		if (main->calc->angle < 0)
			main->calc->angle += main->calc->rad_360;
		calc_step(main);
	}
	else
		return (0);
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
	raycast(main);
    return (0);
}