/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:22:27 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/30 23:19:27 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//translate sprite position to relative to camera or player
// sqrt of pl_to_sp distance not taken bc not needed bc used to find order whih stays same
void		calc_pl_to_sp_dist(t_main *main)
{
	int i;

	i = 0;
	main->pl_to_sp_dist	= cub_calloc(main->sprite_num, sizeof(double), main);
	while (i < main->sprite_num)
	{
		main->pl_to_sp_dist[i] = (
		(main->calc->px - main->sprite[i].sp_gridx) *
		(main->calc->px - main->sprite[i].sp_gridx) +
		(main->calc->py - main->sprite[i].sp_gridy) *
		(main->calc->py - main->sprite[i].sp_gridy));
		printf("%f\n",main->pl_to_sp_dist[i]);
		i++;
	}
}

void		swap_sprite(t_main *main, int a, int b)
{
	double		tmp;
	t_sprite	*tmp_sprite;
	// printf("row %f, col %f texture %f\n", main->sprite[a].sp_gridy, main->sprite[a].sp_gridx, main->pl_to_sp_dist[a]);
	tmp = main->pl_to_sp_dist[a];
	main->pl_to_sp_dist[a] = main->pl_to_sp_dist[b];
	main->pl_to_sp_dist[b] = tmp;
	tmp_sprite = &main->sprite[a];
	main->sprite[a] = main->sprite[b];
	main->sprite[b] = *tmp_sprite;
	// printf("row %f, col %f texture %f\n", main->sprite[a].sp_gridy, main->sprite[a].sp_gridx, main->pl_to_sp_dist[a]);
}

void	sort_sprites(t_main *main)
{
	int		i;
	int		flag;

	calc_pl_to_sp_dist(main);
	flag = 1;
	while (flag)
	{
		flag = 0;
		i = main->sprite_num - 1;
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
	i = 0;
	while (i < main->sprite_num)
	{
		printf("row %f, col %f texture %f\n", main->sprite[i].sp_gridy, main->sprite[i].sp_gridx, main->pl_to_sp_dist[i]);
		i++;
	}
	
}

void	count_sprites(t_main *main)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	row = 0;
	while (row < main->map_height)
	{
		col = 0;
		while (col < main->map_width)
		{
			if (main->map[row][col] == '2')
				i++;
			col++;
		}
		row++;
	}
	main->sprite_num = i;
}

void	init_sprite(t_main *main)
{
	int	row;
	int	col;
	int	i;

	i = 0;
	count_sprites(main);
	main->sprite = (t_sprite *)cub_calloc(main->sprite_num, sizeof(t_sprite), main);
	row = 0;
	while (row < main->map_height && i < main->sprite_num)
	{
		col = 0;
		while (col < main->map_width)
		{
			if (main->map[row][col] == '2')
			{
				main->sprite[i].sp_gridx = col;
				main->sprite[i].sp_gridy = row;
				if (rand() % 2 == 0)
					main->sprite[i].texture = 4;
				else
					main->sprite[i].texture = 5;
				// printf("row %d, col %d texture %d\n", row, col, main->sprite[i].texture);
				i++;
			}
			// else if (main->map[row][col] == 3)
			// {
			// 	// can make door appear sunken by using an offset
			// 	main->sprite[i] = cub_calloc(1, sizeof(t_sprite), main);
			// 	main->sprite[i].x = col;
			// 	main->sprite[i].y = row;
			// 	// if (condition showing door triggered)
			// 		main->sprite[i].texture = 6;
			// 	// next frame
			// 		main->sprite[i].texture = 7;
			// 	// next frame
			// 		main->sprite[i].texture = 8;
			// 	i++;
			// }
			col++;
		}
		row++;
	}
	// free sprite later
}
