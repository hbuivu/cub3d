/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:22:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/24 03:41:03 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void		swap_sprite(t_main *main, int a, int b)
{
	double	    tmp;
	t_sprite	*tmp_sprite;

    tmp_sprite = NULL;
	tmp = main->pl_to_sp_dist[a];
	main->pl_to_sp_dist[a] = main->pl_to_sp_dist[b];
	main->pl_to_sp_dist[b] = tmp;
	tmp_sprite = main->sprite[a];
	main->sprite[a] = main->sprite[b];
	main->sprite[b] = tmp_sprite;
}

void			sort_sprites(t_main *main)
{
	int		i;
	int		flag;

	calc_pl_to_sp_dist(main);
	flag = 1;
	while (flag)
	{
		flag = 0;
		i = NUM_SPRITES - 1;
		while (i > 0)
		{
			if (main->pl_to_sp_dist[i] > main->pl_to_sp_dist[i - 1])
			{
				swap_sprite(main, i, i - 1);
				flag = 1;
			}
			i--;
		}
	}
}