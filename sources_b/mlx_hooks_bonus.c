/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:39:17 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/29 15:26:13 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	mouse_move(int x, int y, t_main *main)
{
	if (y >= 0 && y < WIN_HEIGHT)
	{
		if (x < WIN_WIDTH / 2)
			rotate(LEFT_KEY, main->calc);
		else
			rotate(RIGHT_KEY, main->calc);
	}
	else
		return (0);
	mlx_mouse_move(main->mlx.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	raycast(main);
	return (0);
}
