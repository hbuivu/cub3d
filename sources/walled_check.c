/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walled_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:01:13 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/08 18:52:59 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	visit(t_queue *ptr, t_main *main, int x, int y)
{
	char pos;

	pos = main->map[y][x];
	// printf("pos %c\n",  main->map[y][x]);
	// printf("pos  x %d y %d\n", x, y);
	// pos = main->map[main->player_update[1]][main->player_update[0]];
	// printf("player_update[y]: %i player_update[x]: %i\n", main->player_update[y], main->player_update[x]);
	// if ((main->map[main->player_update[1]][main->player_update[0]] != '1') &&
	if (main->player_update[0] < 0 || main->player_update[0] >= main->map_width ||
		main->player_update[1] < 0 || main->player_update[1] >= main->map_height)
		return_error(main, WALL_ERR);
	if (main->map[main->player_update[1]][main->player_update[0]] == '1')
	//  || main->map_cpy[main->player_update[1]][main->player_update[0]] == 'V')
		return ;
	if (main->map[main->player_update[1]][main->player_update[0]] != '1' || main->map_cpy[main->player_update[1]][main->player_update[0]] != 'V')
	{
		printf("pos %c\n", pos); 
		printf("pos %c\n",  main->map[y][x]);
		printf("queue pos  x %d y %d\n", x, y);
		ft_lstadd_back_dl(&ptr, ft_lstnew_dl(x, y));
		main->map_cpy[main->player_update[1]][main->player_update[0]] = 'V';
		int	i = 0;
		while(main->map_cpy[i])
		{
			printf("%s\n", main->map_cpy[i]);
			i++;
		}
	}
}

void	check_walled_helper(t_queue *ptr, t_main *main)
{
	if ((main->map[main->player_pos[1]][main->player_pos[0]] != '1') &&
		(main->player_pos[0] <= 0 || main->player_pos[0] >= main->map_width - 1 ||
		main->player_pos[1] <= 0 || main->player_pos[1] >= main->map_height - 1))
		return_error(main, WALL_ERR);
	// printf("player_pos %c\n",main->map[main->player_pos[1]][main->player_pos[0]]);
	// printf("player_pos[1]: %i player_pos[0]: %i\n", main->player_pos[1], main->player_pos[0]);
	main->map_cpy[main->player_pos[1]][main->player_pos[0]] = 'V';
	main->player_update = (int *)cub_malloc(2, sizeof(int), main);
	main->player_update[0] = ptr->x;
	main->player_update[1] = ptr->y;
	// printf("player: %c\n", main->map[ptr->y][ptr->x]);
	// printf("player: %c\n", main->map[main->player_pos[1]][main->player_pos[0] + 9]);
	// printf("player_update[1]: %i player_update[0]: %i\n", ptr->y, ptr->x + 1);
	if (main->player_pos[0] - 1 > 0 && main->player_pos[0] + 1 < main->map_width)
	{
		visit(ptr, main, ptr->x + 1, ptr->y);
		visit(ptr, main, ptr->x - 1, ptr->y);
	}
	if (main->player_pos[1] - 1 > 0 && main->player_pos[1]  + 1 < main->map_height)
	{
		visit(ptr, main, ptr->x,ptr->y + 1);
		visit(ptr, main, ptr->x, ptr->y - 1);
	}
	if (main->player_pos[0] - 1 > 0  && main->player_pos[1] - 1 > 0)
		visit(ptr, main, ptr->x - 1,ptr->y - 1);
	if (main->player_pos[0] + 1 < main->map_width && main->player_pos[1]  + 1 < main->map_height)
		visit(ptr, main, ptr->x + 1, ptr->y + 1);
	if (main->player_pos[1] - 1 > 0 && main->player_pos[1]  + 1 < main->map_height)
		visit(ptr, main, ptr->x - 1, ptr->y + 1);
	if (main->player_pos[0] + 1 < main->map_width && main->player_pos[1] - 1 > 0)
		visit(ptr, main, ptr->x + 1, ptr->y - 1);
}

void	check_walled(t_main *main)
{
	t_queue	*enqueue;
	int		i;
	t_queue	*ptr;

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
