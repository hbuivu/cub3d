/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walled_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:01:13 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/04 15:32:40 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	visit(t_queue *ptr, t_main *main, int x, int y)
{
	if ((main->map[main->player_pos[x]][main->player_pos[y]] != '1') &&
		(main->player_pos[1] == 0 || main->player_pos[1] == main->map_width ||
		main->player_pos[0] == 0 || main->player_pos[0] == main->map_height))
	{
		perror("map not surrounded by walls");
		// free
		exit (1);
	}
	if (main->map[main->player_pos[x]][main->player_pos[y]] == '1' ||
		main->map[main->player_pos[x]][main->player_pos[y]] == 'V')
		return ;
	if (main->map[main->player_pos[x]][main->player_pos[y]] == ' ' ||
		main->map[main->player_pos[x]][main->player_pos[y]] == '0')
		ft_lstadd_back_dl(&ptr, ft_lstnew_dl(main->player_pos));
}

void	check_walled_helper(t_queue *ptr, t_main *main)
{
	main->map_cpy[main->player_pos[1]][main->player_pos[0]] = 'V';
	// main->player_content = ptr->content;
	main->player_update = ptr->content;
	printf("player_pos[1]: %i player_pos[0]: %i\n", main->player_pos[1], main->player_pos[0]);
	printf("player: %c\n", main->map[main->player_pos[1]][main->player_pos[0]]);
	visit(ptr, main, main->player_update[0] + 1, main->player_update[1]);
	visit(ptr, main, main->player_update[0] - 1, main->player_update[1]);
	visit(ptr, main, main->player_update[0], main->player_update[1] + 1);
	visit(ptr, main, main->player_update[0], main->player_update[1] - 1);
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
	enqueue = ft_lstnew_dl(main->player_pos);
	ptr = enqueue;
	while (enqueue != NULL)
	{
		check_walled_helper(ptr, main);
		ptr = ptr->next;
		ft_dequeue(enqueue);
		enqueue = ptr;
	}
}

// void	visit(t_queue *ptr, t_main *main, int x, int y)
// {
// 	int i;

// 	printf("visit player_pos[1]: %i player_pos[0]: %i, y%i, x%i\n", main->player_pos[1], main->player_pos[0], y, x);
// 	printf("player: %c\n", main->map[main->player_pos[y]][main->player_pos[x]]);
// 	if ((main->map[main->player_pos[y]][main->player_pos[x]] != '1') &&
// 		(main->player_pos[1] == 0 || main->player_pos[1] == main->map_height ||
// 		main->player_pos[0] == 0 || main->player_pos[0] == main->map_width))
// 	{
// 		perror("map not surrounded by walls");
// 		// free
// 		exit (1);
// 	}
// 	printf("salam\n");
// 	if (main->map[main->player_pos[y]][main->player_pos[x]] == '1' ||
// 		main->map_cpy[main->player_pos[y]][main->player_pos[x]] == 'V')
// 		return ;
// 	if (main->map[main->player_pos[y]][main->player_pos[x]] == ' ' ||
// 		main->map[main->player_pos[y]][main->player_pos[x]] == '0')
// 		ft_lstadd_back_dl(&ptr, ft_lstnew_dl(main->player_pos));
// 	main->map_cpy[main->player_pos[y]][main->player_pos[x]] = 'V';
// 	i = 0;
// 	while(main->map_cpy[i])
// 	{
// 		printf("%s\n", main->map_cpy[i]);
// 		i++;
// 	}
// }

// void	check_walled_helper(t_queue *ptr, t_main *main)
// {
// 	// int i;

// 	main->map_cpy[main->player_pos[1]][main->player_pos[0]] = 'V';
// 	// i = 0;
// 	// while(main->map_cpy[i])
// 	// {
// 	// 	printf("%s\n", main->map_cpy[i]);
// 	// 	i++;
// 	// }
// 	main->player_update = ptr->content;
// 	printf("player_pos[1]: %i player_pos[0]: %i\n", main->player_pos[1], main->player_pos[0]);
// 	printf("player: %c\n", main->map[main->player_pos[1] + 1][main->player_pos[0]]);
// 	visit(ptr, main, main->player_update[0] + 1, main->player_update[1]);
// 	visit(ptr, main, main->player_update[0] - 1, main->player_update[1]);
// 	visit(ptr, main, main->player_update[0], main->player_update[1] + 1);
// 	visit(ptr, main, main->player_update[0], main->player_update[1] - 1);
// }

// void	check_walled(t_main *main)
// {
// 	t_queue	*enqueue;
// 	int		i;
// 	t_queue	*ptr;

// 	main->map_cpy = ft_calloc(main->map_height + 1, sizeof(char*));
// 	i = 0;
// 	while (main->map[i])
// 	{
// 		main->map_cpy[i] = ft_strdup(main->map[i]);
// 		i++;
// 	}
// 	// i = 0;
// 	// while(map_cpy[i])
// 	// {
// 	// 	printf("%s\n", map_cpy[i]);
// 	// 	i++;
// 	// }
// 	enqueue = ft_lstnew_dl(main->player_pos);
// 	ptr = enqueue;
// 	while (enqueue != NULL)
// 	{
// 		check_walled_helper(ptr, main);
// 		ptr = ptr->next;
// 		ft_dequeue(enqueue);
// 		enqueue = ptr;
// 	}
// }