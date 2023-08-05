#include "../include/cub3D.h"

void	calc_step(t_main *main)
{
	if (main->calc->angle < 90 || main->calc->angle > 270)
		main->calc->stepx = 1;
	if (main->calc->angle == 90 || main->calc->angle == 270)
		main->calc->stepx = 0;
	if (main->calc->angle > 90 && main->calc->angle < 270)
		main->calc->stepx = -1;
	if (main->calc->angle > 0 && main->calc->angle < 180)
		main->calc->stepy = -1;
	if (main->calc->angle == 0 || main->calc->angle == 180)
		main->calc->stepy = 0;
	if (main->calc->angle > 180 && main->calc->angle < 360)
		main->calc->stepy = 1;
}

void	init_calc(t_main *main)
{
	main->calc->upg = 64;
	main->calc->fov = 66;
	main->calc->r_fov = main->calc->fov * (M_PI / 180);
	main->calc->pln_width = main->win_width;
	main->calc->pln_height = main->win_height;
	main->calc->pln_dist = (main->calc->pln_width / 2) / tan(main->calc->fov / 2);
	main->calc->ray_incr = main->calc->fov / main->calc->pln_width;
	if (main->player_dir == 'E')
		main->calc->pdir = 0;
	else if (main->player_dir == 'N')
		main->calc->pdir = 90;
	else if (main->player_dir == 'W')
		main->calc->pdir = 180;
	else if (main->player_dir == 'S')
		main->calc->pdir = 270;
	main->calc->angle = main->calc->pdir - (main->calc->fov / 2)
	main->calc->r_angle = main->calc->angle * (M_PI / 180);
	if (main->calc->angle < 0)
		main->calc->angle += (2 * M_PI);
	main->calc->px = (((double)main->player_pos[0] + .5) * main->calc->upg);
	main->calc->py = (((double)main->player_pos[1] - .5) * main->calc->upg);
	calc_step(main);
}

int	round_down(double num)
{
	return (num);
}

int	round_up(double num)
{
	return (num + 1);
}

void	raycast(t_main *main)
{
	t_calc	*c;

	init_calc(main);
	c = main->calc;
	
	//find deltax and deltay (use deltay with col, and deltax with row)
	//the ray moves for deltay each time it jumps one column
	//the ray moves for deltax each time it jumps one row
	c->deltax = fabs(c->upg / tan(c->r_angle));
	c->deltay = fabs(c->upg * tan(c->r_angle));

	//find first column intersection from starting position
	// for cstepx/cstepy== -1. we subtract 1 so it takes us into the column to the left of us when we check. otherwise we are stuck in the our current box
	if (c->stepx == 1)
		c->col_int = round_up(c->px / c->upg) * c->upg;
	else if (c->stepx == -1)
		c->col_int = round_down(c->px / c->upg) * c->upg - 1; 
	c->col_int_y = c->py + (c->stepy * fabs((c->col_int - c->px) * tan(c->r_angle)));

	//find first row intersection from starting position
	if (c->stepy == 1)
		c->row_int = round_up(c->px / c->upg) * c->upg;
	else if (c->stepy == -1)
		c->row_int = round_down(c->px / c->upg) * c->upg - 1;
	c->row_int_x = c->px + (c->stepx * fabs((c->row_int - c->py) / tan(c->r_angle)));

	// while (main->map[(int)(c->col_int / c->upg)][(int)(c->col_int_y / c->upg)] != 1)
	// {
	// 	c->col_int += c->stepx * c->upg;
	// 	c->col_int_y += c->stepy * c->deltay;
	// }
	// while (main->map[(int)(c->row_int_x / c->upg)][(int)(c->row_int / c->upg)] != 1)
	// {
	// 	c->row_int += c->stepy * c->upg;
	// 	c->row_int_x += c->stepx * c->deltax;
	// }


	
}	

	// //find first intersect on columns.
	// if (c->stepx == 1)
	// 	c->col_pt = c->px + (c->stepx * (c->ugp - c->px % c->ugp));
	// else if (c->xstep == -1)
	// 	c->col_pt = c->px + (c->stepx * (c->px % c->ugp) - 1);
	// c->col_pty = c->py + (c->stepy * (c->col_pt - c->px) * tan(c->alpha));
	// c->deltax = c->upg * tan(c->angle);
	// c->ch_col = c->col_pt;
	// c->ch_row = c->col_pty;
	// while(main->map[c->ch_col][c->ch_row] != 1)
	// {
	// 	c->col_pt += (c->upg * c->stepx);
	// 	c->col_pty += c->deltax;
	// 	c->ch_col = c->col_pt;
	// 	c->ch_row = c->col_pty;
	// }
	// if (c->stepy == 1)
	// 	c->row_pt = c->py + (c->stepy * (c->ugp - c->py % c->ugp));
	// else if (c->stepy == -1)
	// 	c->row_pt = c->py + (c->stepy * (c->py % c->ugp) - 1);
	// c->row_ptx = c->px + ((c->row_pt = c->py)/tan(c->angle));
	// c->deltay = 64 / tan(c->angle);
	// c->ch_col = c->row_ptx;
	// c->ch_row = c->row_pt;
	// while(main->map[c->ch_col][c->ch_row] != 1)
	// {
	// 	c->col_pt += (c->upg * c->stepx);
	// 	c->col_pty += c->deltax;
	// 	c->ch_col = c->col_pt;
	// 	c->ch_row = c->col_pty;
	// }
	// 	//record perpendicular distance to wall