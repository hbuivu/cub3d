/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/17 23:39:28 by hbui-vu          ###   ########.fr       */
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
	else if (key_code == A_KEY)
	{
		while (--i < 2)
		{
			if (fmod(main->calc->px, 64) == 0 && main->map[(int)(main->calc->py / 64)][(int)((main->calc->px / 64) - 1)] == '1')
				break;
			// if (fmod(main->calc->px, 64) == 0 && fmod(main->calc->py, 64) == 0)
			// 	if (main->map[])
			main->calc->px--;
		}
	}
	else if (key_code == D_KEY)
	{
		while (++i < 2)
		{
			if (main->map[(int)(main->calc->py / 64)][(int)((main->calc->px / 64))] == '1')
				break;
			main->calc->px++;
		}
	}
	else if (key_code == W_KEY)
	{
		while (--i < 2)
		{
			if (fmod(main->calc->py, 64) == 0 && main->map[(int)((main->calc->py / 64) - 1)][(int)(main->calc->px / 64)] == '1')
				break;
			main->calc->py--;
		}
	}
	else if (key_code == S_KEY)
	{
		while (++i < 2)
		{
			if (main->map[(int)(main->calc->py / 64)][(int)((main->calc->px / 64))] == '1')
				break;
			main->calc->py++;
		}
	}
	// mlx_clear_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	// mlx_destroy_image(main->mlx.mlx_ptr, main->img.img);
	raycast(main);
    return (0);
}