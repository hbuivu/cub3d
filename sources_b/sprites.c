/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:30:29 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/29 16:02:24 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	reset_sprite_search(t_main *main)
{
	t_sprite	*sp;
	int			i;
	
	sp = main->sprite;
	i = 0;
	while (i < main->sprite_num)
	{
		sp[i].render = 0;
		i++;
	}
}

void	search_sprite(int row, int col, t_main *main)
{
	t_sprite	*sp;
	int			i;

	sp = main->sprite;
	i = 0;
	while (i < main->sprite_num)
	{
		if (ch_num(sp[i].x, (double)col) && ch_num(sp[i].y, (double)row))
		{
			if (sp[i].render == 0)
			{
				sp[i].render = 1;
				//project sprite onto 2d screen - find screen position
				//projected sprite height = (actual sprite height / actual distance from player) * distance of player to projection plane
				
			}
			//run calculations
			/* sprite height is 16
				we know the box in which the sprite resides
				we can render the sprite based on distance from the player 
				make sure when drawing sprite that either the top or bottom stays the same
				it does not always stay in the middle 
				sprite collision??
				*/
			
			return ;
		}
		i++;
	}
	
}