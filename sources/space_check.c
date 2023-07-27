/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:01:13 by zsyyida           #+#    #+#             */
/*   Updated: 2023/07/27 10:41:54 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	ft_valid_path_visit(t_queue *ptr, t_map *map, int position)
{
	if (map->str_map[position] == '1' || map->str[position] == 'V')
		return ;
	if (map->str_map[position] == ' ' || map->str_map[position] == '0')
	{
		if (map->str_map[position] == ' ')
		{
			perror("Error\n Path is not valid, player can reach a space");
			free (map->str);
			exit (0);
		}
		ft_lstadd_back_dl(&ptr, ft_lstnew_dl(position));
		map->str[position] = 'V';
	}
}

void	ft_valid_path_helper(t_queue *ptr, t_map *map)
{
	map->str[map->player] = 'V';
	map->player_update = ptr->content;
	ft_valid_path_visit(ptr, map, (map->player_update + 1));
	ft_valid_path_visit(ptr, map, (map->player_update - 1));
	ft_valid_path_visit(ptr, map, (map->player_update - map->width - 1));
	ft_valid_path_visit(ptr, map, (map->player_update + map->width + 1));
}

void	ft_valid_path(t_map map)
{
	t_queue	*enqueue;
	int		i;
	t_queue	*ptr;

	i = 0;
	map.str = ft_strdup((char *)map.str_map);
	enqueue = ft_lstnew_dl(map.player);
	ptr = enqueue;
	while (enqueue != NULL)
	{
		ft_valid_path_helper(ptr, &map);
		ptr = ptr->next;
		ft_dequeue(enqueue);
		enqueue = ptr;
	}
}