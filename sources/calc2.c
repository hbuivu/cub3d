/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:37:15 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/26 15:38:23 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	recalc(t_main *main)
{
	t_calc	*c;

	c = main->calc;
	c->angle += c->ray_incr;
	if (c->angle < 0)
		c->angle += c->rad_360;
	else if (c->angle > c->rad_360 || ch_num(c->angle, c->rad_360))
		c->angle -= c->rad_360;
	c->tan_angle = tan(c->angle);
	calc_step(main);
}
