/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 20:51:30 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/08 21:02:09 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* change to print new image on top after updating x and y
	ft_printf("keycode = %d\n", key_code);
 do not use else if or game stops
*/
int	ft_movement(int key_code, t_main *main)
{
	if (key_code == ESC)
		ft_close(main);
	// if (key_code == LEFT_KEY || key_code == A_KEY)

	// if (key_code == RIGHT_KEY || key_code == D_KEY)

	// if (key_code == UP_KEY || key_code == W_KEY)

	// if (key_code == DOWN_KEY || key_code == S_KEY)

    return (0);
}