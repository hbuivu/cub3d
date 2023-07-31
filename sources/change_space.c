

#include "../include/cub3D.h"

void	visit(t_queue *ptr, t_main *main, int x, int y)
{
	if (main->map[main->player_pos[x]][main->player_pos[y]] == '1' || main->map[main->player_pos[x]][main->player_pos[y]]  == 'V')
		return ;
	if (main->map[main->player_pos[x]][main->player_pos[y]]  == ' ' || main->map[main->player_pos[x]][main->player_pos[y]]  == '0')
		main->map[main->player_pos[x]][main->player_pos[y]]  = 'V';
	{
		ft_lstadd_back_dl(&ptr, ft_lstnew_dl(main->map[main->player_pos[x]][main->player_pos[y]]));
		// map->str[position] = 'V';
	}
}

void	change_space_helper(t_queue *ptr, t_main *main)
{
	main->player_content = ptr->content;

	visit(ptr, main, main->player_update[0] + 1, main->player_update[1]);
	visit(ptr, main, main->player_update[0] - 1, main->player_update[1]);
	visit(ptr, main, main->player_update[0], main->player_update[1] + 1);
	visit(ptr, main, main->player_update[0], main->player_update[1] - 1);
}

void	change_space(t_main *map)
{
	t_queue	*enqueue;
	int		i;
	t_queue	*ptr;

	i = 0;
	// map.str = ft_strdup((char *)map->map);
	enqueue = ft_lstnew_dl(map->player_pos);
	ptr = enqueue;
	while (enqueue != NULL)
	{
		change_space_helper(ptr, map);
		ptr = ptr->next;
		ft_dequeue(enqueue);
		enqueue = ptr;
	}
}
