#include "../include/cub3D.h"

void	print_omap(t_omap *map)
{
	t_omap *row;

	if (!map)
		return ;
	row = map;
	while (row)
	{
		printf("%s", row->row);
		row = row->next;
	}
}