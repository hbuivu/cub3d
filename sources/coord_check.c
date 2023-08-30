/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:38:42 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/30 13:59:05 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//check for corner only if stepx and stepy in pos direction
int	col_jump(t_main *main)
{
	int		row;
	int		col;
	t_calc	*c;

	c = main->calc;
	if (c->stepx == 1 && c->stepy == 1
		&& ch_num(fmod(c->col_int, UPG), 0)
		&& ch_num(fmod(c->col_inty, UPG), 0))
	{
		col = (c->col_int / UPG) - 1; 
		row = c->col_inty / UPG;
	}
	else
	{
		row = c->col_inty / UPG;
		if (c->stepx == -1)
			col = (c->col_int / UPG) - 1;
		else
			col = c->col_int / UPG;
	}
	if (c->col_inty > 0 && c->col_int > 0 && row < main->map_height
		&& col < main->map_width && main->map[row][col] != '1')
		return (1);
	return (0);
}

int	row_jump(t_main *main)
{
	int		row;
	int		col;
	t_calc	*c;

	c = main->calc;
	if (c->stepx == 1 && c->stepy == 1
		&& ch_num(fmod(c->row_int, UPG), 0)
		&& ch_num(fmod(c->row_intx, UPG), 0))
	{
		row = (c->row_int / UPG) - 1;
		col = c->row_intx / UPG; 
	}
	else
	{
		col = c->row_intx / UPG;
		if (c->stepy == -1)
			row = (c->row_int / UPG) - 1;
		else
			row = c->row_int / UPG;
	}
	if (c->row_intx > 0 && c->row_int > 0 && row < main->map_height
		&& col < main->map_width && main->map[row][col] != '1')
		return (1);
	return (0);
}

//returns 0 if wall detected
int	check_coord(int jump, t_main *main)
{
	if (jump == COL)
		return (col_jump(main));
	else if (jump == ROW)
		return (row_jump(main));
	return (0);
}
