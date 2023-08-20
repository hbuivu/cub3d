#include "../include/cub3D.h"

//use check coordinate to check for corners too?
int	col_jump(t_main *main)
{
	int		row;
	int		col;
	t_calc	*c;

	c = main->calc;
	row = c->col_inty / c->upg;
	if (c->stepx == -1)
		col = (c->col_int / c->upg) - 1;
	else
		col = c->col_int / c->upg;
	if (c->col_inty > 0 && c->col_int > 0 && row < main->map_height &&
		col < main->map_width && main->map[row][col] != '1')
		return (1);
	reurn (0);
}

int	row_jump(t_main *main)
{
	int		row;
	int		col;
	t_calc	*c;

	c = main->calc;
	col = c->row_intx / c->upg;
	if (c->stepy == -1)
		row = (c->row_int / c->upg) - 1;
	else
		row = c->row_int / c->upg;
	if (c->row_intx > 0 && c->row_int > 0 && row < main->map_height &&
		col < main->map_width && main->map[row][col] != '1')
		return (1);
	return (0);
}

int	check_coord(int jump, t_main *main)
{
	//check for corners
	if (jump == COL)
		return (col_jump(main));
	else if (jump == ROW)
		return (row_jump(main));
	return (0);
}
