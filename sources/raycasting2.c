#include "../include/cub3D.h"

int	found_wall(int col, int row, t_main *main)
{
	if (main->map[col][row] == '1')
		return (1);
	return (0);
}

void	init_calc(t_main *main)
{
	main->calc.upg = 64;
	main->calc.fov = 66 * (M_PI / 180);
	main->calc.pln_width = main->win_width;
	main->calc.pln_height = main->win_height;
	main->calc.pln_dist = (main->calc.pln_width / 2) / tan(main->calc.fov / 2);
	main->calc.ray_incr = main->calc.fov / main->calc.pln_width;
	if (main->player_dir == 'E')
		main->calc.pl_dir = 0 * (M_PI / 180);
	else if (main->player_dir == 'N')
		main->calc.pl_dir = 90 * (M_PI / 180);
	else if (main->player_dir == 'W')
		main->calc.pl_dir = 180 * (M_PI / 180);
	else if (main->player_dir == 'S')
		main->calc.pl_dir = 270 * (M_PI / 180);
	main->calc.angle = main->calc.pl_dir - (main->calc.fov/2);
	main->calc.pl_x = (((double)main->player_pos[0] + .5) * main->calc.upg);
	main->calc.pl_y = (((double)main->player_pos[1] + .5) * main->calc.upg);
}

void	calc_step(t_main *main)
{
	if (main->calc.angle == 0)
	{
		main->calc.stepx = 1;
		main->calc.stepy = 0;
	}
	else if (main->calc.angle < 90 * (M_PI / 180))
	{
		main->calc.stepx = 1;
		main->calc.stepy = -1;
	}
	else if (main->calc.angle == 90 * (M_PI / 180))
	{
		main->calc.stepx = 0;
		main->calc.stepy = 1;
	}
	else if (main->calc.angle < 180 * (M_PI / 180))
	{
		main->calc.stepx = -1;
		main->calc.stepy = -1;
	}
	else if (main->calc.angle == 180 * (M_PI / 180))
	{
		main->calc.stepx = -1;
		main->calc.stepy = 0;
	}
	else if (main->calc.angle < 270 * (M_PI / 180))
	{
		main->calc.stepx = -1;
		main->calc.stepy = 1;
	}
	else if (main->calc.angle == 270 * (M_PI / 180))
	{
		main->calc.stepx = 0;
		main->calc.stepy = 1;
	}
	else if (main->calc.angle < 360 * (M_PI / 180))
	{
		main->calc.stepx = -1;
		main->calc.stepy = 1;
	}
	else if (main->calc.angle == 360 * (M_PI / 180))
	{
		main->calc.stepx = 1;
		main->calc.stepy = 0;
	}
}

void	raycasting(t_main *main)
{
	t_calc	c;

	init_calc(main);
	calc_sep(main);
	c = main->calc;
	//cast a ray and trace until it hits a wall
	//find first intersect on columns
	c.col_pt = ((int)(c.pl_x / c.upg) * c.upg) + c.stepy; 
	c.col_pty = (tan(c.angle) * (c.col_pt - c.pl_x)) + c.pl_y;
	c.ch_col = c.col_pt;
	c.ch_row = c.col_pty;                    

	//record perpendicular distance to wall


	
}	