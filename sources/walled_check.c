/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walled_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:01:13 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/09 17:19:00 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_queue(t_queue *queue)
{
	t_queue	*ptr;

	ptr = queue;
	while (ptr != NULL)
	{
		printf("queue x %d y %d\n", ptr->x, ptr->y);
		ptr = ptr->next;
	}
}

void	visit(t_queue *ptr, t_main *main, int x, int y)
{
	char	pos;

	pos = main->map_cpy[y][x];
	if ((pos != '1') && (x <= 0 || x >= main->map_width - 1 || y <= 0
			|| y >= main->map_height - 1))
		return_error(main, WALL_ERR);
	if (pos == '1' || pos == 'V')
		return ;
	if (pos != '1' || pos != 'V')
	{
		ft_lstadd_back_dl(&ptr, ft_lstnew_dl(x, y));
		main->map_cpy[y][x] = 'V';
	}
}

void	check_walled_helper(t_queue *ptr, t_main *main)
{
	// if (main->player_pos[0] <= 0 || main->player_pos[0] >= main->map_width - 1
	// 	|| main->player_pos[1] <= 0 || main->player_pos[1] >= main->map_height - 1)
	// 	return_error(main, WALL_ERR);
	main->map_cpy[main->player_pos[1]][main->player_pos[0]] = 'V';
	main->player_update[0] = ptr->x;
	main->player_update[1] = ptr->y;
	if (ptr->x - 1 > 0 && ptr->x + 1 < main->map_width)
	{
		visit(ptr, main, ptr->x + 1, ptr->y);
		visit(ptr, main, ptr->x - 1, ptr->y);
	}
	if (main->player_update[1] - 1 > 0 && main->player_update[1] + 1 < main->map_height)
	{
		visit(ptr, main, ptr->x, ptr->y + 1);
		visit(ptr, main, ptr->x, ptr->y - 1);
	}
	if (main->player_update[0] - 1 > 0 && main->player_update[1] - 1 > 0)
		visit(ptr, main, ptr->x - 1, ptr->y - 1);
	if (main->player_update[0] + 1 < main->map_width
		&& main->player_update[1] + 1 < main->map_height)
		visit(ptr, main, ptr->x + 1, ptr->y + 1);
	if (main->player_update[1] - 1 > 0 && main->player_update[1] + 1 < main->map_height)
		visit(ptr, main, ptr->x - 1, ptr->y + 1);
	if (main->player_update[0] + 1 < main->map_width && main->player_update[1] - 1 > 0)
		visit(ptr, main, ptr->x + 1, ptr->y - 1);
}

void	check_walled(t_main *main)
{
	t_queue	*enqueue;
	int		i;
	t_queue	*ptr;

	main->player_update = (int *)cub_malloc(2, sizeof(int), main);
	main->map_cpy = ft_calloc(main->map_height + 1, sizeof(char*));
	i = 0;
	while (main->map[i])
	{
		main->map_cpy[i] = ft_strdup(main->map[i]);
		i++;
	}
	enqueue = ft_lstnew_dl(main->player_pos[0], main->player_pos[1]);
	ptr = enqueue;
	while (enqueue != NULL)
	{
		check_walled_helper(ptr, main);
		ptr = ptr->next;
		ft_dequeue(enqueue);
		enqueue = ptr;
	}
}
