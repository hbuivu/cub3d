#include "../include/cub3D.h"

void	print_omap(t_omap *map)
{
	t_omap *row;

	if (!map)
		return ;
	row = map;
	while (row)
	{
		printf("%s\n", row->row);
		row = row->next;
	}
}

void	print_main_map(t_main *main)
{
	int i;

	i = 0;
	while (main->map[i])
	{
		printf("%s\n", main->map[i]);
		i++;
	}
}