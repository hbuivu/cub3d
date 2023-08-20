/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/20 12:07:56 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*
 Destroy a window instance.
	int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
 @param	void *mlx_ptr	the mlx instance;
 @param	void *mlx_win	the window instance;
 @return	int				has no return value (bc).
*/
int	ft_close(t_main *main)
{
	mlx_destroy_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	// free(main->map);
	exit(0);
}

void	move(t_main *main)
{
	//get pdir
	
}
/* change to print new image on top after updating x and y
	ft_printf("keycode = %d\n", key_code);
 do not use else if or game stops
*/

//NOTE: Check if this works w floats

int	key_press(int key_code, t_main *main)
{
	int	i = -1;

	if (key_code == ESC)
		ft_close(main);
	if (key_code == LEFT_KEY)
	{
		main->calc->pdir -= 0.0349066; //2 degrees
		if (main->calc->pdir < 0)
			main->calc->pdir += main->e_angle;
		main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
		if (main->calc->angle < 0)
			main->calc->angle += 2 * M_PI;
		calc_step(main);
	}
	else if (key_code == RIGHT_KEY)
	{
		main->calc->pdir += 0.0349066; //2 degrees
		if (main->calc->pdir > main->e_angle)
			main->calc->pdir -= main->e_angle;
		main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
		if (main->calc->angle < 0)
			main->calc->angle += 2 * M_PI;
		calc_step(main);
	}
	//check for every step if it takes you into a wall
	else if (key_code == W_KEY) //NORTH
	{
		for (int i; i < 5; i++)
		{
			if (ch_num(fmod(main->calc->px, 64.0), 0))
				if (!check_coord(COL, main))
					break;
			else if (ch_num(fmod(main->calc->py, 64.0), 0))
				if (check_coord(ROW, main))
					break;
			main->calc->px += cos(main->calc->pdir) * main->calc->stepx;
			main->calc->py += sin(main->calc->pdir) * main->calc->stepy;			
		}
		
	}
	else if (key_code == S_KEY) //SOUTH
	{
		main->calc->px += cos(main->calc->pdir) * main->calc->stepx * -1;
		main->calc->py += sin(main->calc->pdir) * main->calc->stepy * -1;
	}
	else if (key_code == D_KEY) //EAST
	{
		main->calc->px += sin(main->calc->pdir) * main->calc->stepx;
		main->calc->py += cos(main->calc->pdir) * main->calc->stepy * -1;
	}
	else if (key_code == A_KEY) //WEST
	{
		main->calc->px += sin(main->calc->pdir) * main->calc->stepx * -1;
		main->calc->py += cos(main->calc->pdir) * main->calc->stepy;
	}
	raycast(main);
    return (0);
}