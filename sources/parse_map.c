/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:14:26 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/19 12:19:40 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// // checks for anything after map (after a line with only spaces)
// void	check_map(t_main *main)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y + 1 < main->map_height)
// 	{
// 		x = 0;
// 		if ((ft_strchr("NSEW01", main->map[y][x++]) == 0) &&
// 			(ft_strchr("NSEW01", main->map[y + 1][x++]) != 0))
// 			return_error(main, MAP_ERR);
// 		y++;
// 	}
// }

void	get_map(t_omap *ptr_map, t_main *main)
{
	t_omap	*cur;
	int		i;
	int		j;

	i = -1;
	j = -1;
	cur = ptr_map;
	main->map = (char **)cub_calloc(main->map_height + 1, sizeof(char *), main);
	while (++i < main->map_height)
	{
		main->map[i] = (char *)cub_calloc(main->map_width + 1, sizeof(char), main);
		while (cur->row[++j])
			main->map[i][j] = cur->row[j];
		//should we replace with 0's instead?
		while (j < main->map_width)
		{
			// main->map[i][j] = ' ';
			main->map[i][j] = '0';
			j++;
		}
		j = -1;
		cur = cur->next;
	}
	// check_map(main);
}

void	check_map_char(char c, int i, t_main *main)
{
	if (ft_strchr(" NSEW01", c) == 0)
		return_error(main, MAP_ERR);
	if (ft_strchr("NSEW", c))
	{
		if (main->player_dir != '\0' || main->player_pos != NULL)
			return_error(main, PLAYER_ERR);
		main->player_dir = cur->row[i];
		main->player_pos = (int *)cub_malloc(2, sizeof(int), main);
		main->player_pos[0] = i;
		main->player_pos[1] = main->map_height;
	}
}

void	parse_map(t_omap *omap_start, t_main *main)
{
	t_omap	*cur;
	int		i;
	
	//check with Zahra if identify returns NULL
	if (omap_start == NULL)
		return_error(main, MAP_ERR);
	cur = omap_start;
	i = -1;
	while (cur)
	{
		if (cur->row[0] == '\n')
			return_error(main, MAP_ERR);
		while (cur->row[++i])
			check_map_char(cur->row[i], i, main);
		main->map_height++;
		if (main->map_width < i)
			main->map_width = i;
		i = 0;
		cur = cur->next;
	}
	if (main->player_dir == '\0')
		return_error(main, MAP_ERR);
	get_map(omap_start, main);
}
