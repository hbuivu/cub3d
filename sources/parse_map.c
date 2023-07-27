/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:14:26 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/07/27 19:45:49 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//does not check for if there are multiple spaces after end of map
//-> delete all spaces at the end in download.c

void	parse_map(t_omap *omap_start, t_main *main)
{
	t_omap	*cur;
	int		i;
	// int		j;
	
	cur = omap_start;
	i = 0;
	//first iteration
	while (cur)
	{
		while (cur->row[i])
		{
			if (ft_strchr(" NSEW01", cur->row[i]) == 0)
				return_error(main);
			if (ft_strchr("NSEW", cur->row[i]))
			{
				if (main->player_dir != '\0' || main->player_pos != NULL)
					return_error(main);
				main->player_dir = cur->row[i];
				main->player_pos = (int *)cub_malloc(2, sizeof(int), main);
				main->player_pos[0] = i;
				main->player_pos[1] = main->map_height;
			}
			i++;
		}
		main->map_height++;
		if (main->map_width < i)
			main->map_width = i;
		i = 0;
		cur = cur->next;
	}
	printf("map_height: %i\n", main->map_height);
	printf("map_width: %i\n", main->map_width);
	printf("player position (col, row): %i, %i\n", main->player_pos[0], main->player_pos[1]);
	printf("player dir: %c\n", main->player_dir);
	// //second iteration
	// i = 0;
	// j = 0;
	// main->map = (char **)cub_calloc(main->map_height, sizeof(char *), main);
	// while (i < main->height)
	// {
	// 	main->map[i] = (char *)cub_calloc(main->map_width + 1, sizeof(char), main);
	// 	while (main->omap->row[j])
	// 	{
	// 		main->map[i][j] = main->omap->row[j];
	// 		j++;
	// 	}
	// 	while (j < main->map_width)
	// 	{
	// 		main->map[i][j] = ' ';
	// 		j++;
	// 	}
	// 	j = 0;
	// 	i++;
	// }
	
}
