/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:38:42 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/29 15:30:17 by hbui-vu          ###   ########.fr       */
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
		&& ch_num(fmod(c->col_int, c->upg), 0)
		&& ch_num(fmod(c->col_inty, c->upg), 0))
	{
		col = (c->col_int / c->upg) - 1; 
		row = c->col_inty / c->upg;
	}
	else
	{
		row = c->col_inty / c->upg;
		if (c->stepx == -1)
			col = (c->col_int / c->upg) - 1;
		else
			col = c->col_int / c->upg;
	}
	if (c->col_inty > 0 && c->col_int > 0 
		&& row < main->map_height && col < main->map_width)
	{
		if (main->map[row][col] == '2')
		{
			search_sprite(row, col, main);
			return (1);
		}
		else if (main->map[row][col] != '1')
			return (1);
	}
	return (0);
}

int	row_jump(t_main *main)
{
	int		row;
	int		col;
	t_calc	*c;

	c = main->calc;
	if (c->stepx == 1 && c->stepy == 1
		&& ch_num(fmod(c->row_int, c->upg), 0)
		&& ch_num(fmod(c->row_intx, c->upg), 0))
	{
		row = (c->row_int / c->upg) - 1;
		col = c->row_intx / c->upg; 
	}
	else
	{
		col = c->row_intx / c->upg;
		if (c->stepy == -1)
			row = (c->row_int / c->upg) - 1;
		else
			row = c->row_int / c->upg;
	}
	if (c->row_intx > 0 && c->row_int > 0 
		&& row < main->map_height && col < main->map_width)
	{
		if (main->map[row][col] == '2')
		{
			search_sprite(row, col, main);
			return (1);
		}
		else if (main->map[row][col] != '1')
			return (1);
	}
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
