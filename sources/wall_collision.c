#include "../include/cub3D.h"

/* 
1. cast a ray in pdir to find player distance to the nearest wall
2. find player distance traveled with one step
3. player should not be able to move right up against the wall. there should be a small (4 pixel) buffer
3. compare the two distances with buffer
	-if player-to-wall-dist - buff >= player-walk-dist => okay
	-if player-to-wall-dist - buff < player-walk-dist =>
		walk only the amount of steps possible up until wall-buff*/

/* second idea
1. move player to new px and py position
2. check px and py to see if it is in a wall
3. if it's in a wall, return player to original position
*/

double	cast_pdir_hv_ray(char line_dir, t_calc *c, t_main *main)
{
	if (line_dir == 'h')
	{
		c->deltay = 0;
		c->deltax = 64;
		if (c->pdir_stepx == 1)
			c->col_int = ceil(c->px / c->upg) * c->upg;
		else if (c->pdir_stepx == -1)
			c->col_int = floor(c->px / c->upg) * c->upg; 
		c->col_inty = c->py;
		while (check_coord(COL, main))
			c->col_int += c->pdir_stepx * c->deltax;
		return (fabs(c->col_int - c->px));
	}
	c->deltay = 64;
	c->deltax = 0;
	if (c->pdir_stepy == 1)
		c->row_int = ceil(c->py / c->upg) * c->upg;
	else if (c->pdir_stepy == -1)
		c->row_int = floor(c->py / c->upg) * c->upg;
	c->row_intx = c->px;
	while (check_coord(ROW, main))
		c->row_int += c->pdir_stepy * c->deltay;
	return (fabs(c->row_int - c->py));
}

double	cast_pdir_ray(t_calc *c, t_main *main)
{
	c->deltay = fabs(c->upg * c->tan_pdir);
	c->deltax = fabs(c->upg / c->tan_pdir);
	if (c->pdir_stepx == 1)
		c->col_int = ceil(c->px / c->upg) * c->upg;
	else if (c->pdir_stepx == -1)
		c->col_int = floor(c->px / c->upg) * c->upg;
	c->col_inty = c->py + (c->pdir_stepy * fabs((c->col_int - c->px) * c->tan_pdir));
	if (c->pdir_stepy == 1)
		c->row_int = ceil(c->py / c->upg) * c->upg;
	else if (c->pdir_stepy == -1)
		c->row_int = floor(c->py / c->upg) * c->upg;
	c->row_intx = c->px + (c->pdir_stepx * fabs((c->row_int - c->py) / c->tan_pdir));
	while (check_coord(COL, main))
	{
		c->col_int += c->pdir_stepx * c->upg;
		c->col_inty += c->pdir_stepy * c->deltay;
	}
	while (check_coord(ROW, main))
	{
		c->row_int += c->pdir_stepy * c->upg;
		c->row_intx += c->pdir_stepx * c->deltax;
	}
	c->dist_col = fabs((c->px - c->col_int) / cos(c->angle));
	c->dist_row = fabs((c->px - c->row_intx) / cos(c->angle));
	if (c->dist_col <= c->dist_row)
		return (c->dist_col);
	else
		return (c->dist_row);
}

void	calc_move_dist(int key_code, t_main *main)
{
	t_calc *c;

	c = main->calc;
	if (key_code == W_KEY || key_code == S_KEY)
	{
		c->x_walk = fabs(cos(c->pdir)) * WALK; //should we round bc the player cannot walk half a pixel
		c->y_walk = fabs(sin(c->pdir)) * WALK;
		c->x_run = fabs(cos(c->pdir)) * RUN;
		c->y_run = fabs(sin(c->pdir)) * RUN;
		// c->walk_dist = c->x_walk * fabs(cos(c->pdir));
		// c->run_dist = c->x_run * fabs(cos(c->pdir));
		c->walk_dist = 
		c->run_dist = RUN;
	}
	else if (key_code == A_KEY || key_code == D_KEY)
	{
		c->x_walk = fabs(sin(c->pdir)) * WALK;
		c->y_walk = fabs(cos(c->pdir)) * WALK;
		c->x_run = fabs(sin(c->pdir)) * RUN;
		c->y_run = fabs(cos(c->pdir)) * RUN;
		c->walk_dist = c->y_walk * fabs(cos(c->pdir));
		c->run_dist = c->y_run * fabs(cos(c->pdir));
	}
}

void	check_collision(int key_code, t_main *main)
{
	t_calc	*c;
	double	wall_dist;

	c = main->calc;
	if (ch_num(c->pdir, 0) || ch_num(c->pdir, M_PI))
		wall_dist = cast_pdir_hv_ray('h', c, main);
	else if (ch_num(c->pdir, c->rad_90) || ch_num(c->pdir, c->rad_270))
		wall_dist = cast_pdir_hv_ray('v', c, main);
	else
		wall_dist = cast_pdir_ray(c, main);
	calc_move_dist(key_code, main);
	printf("wall_dist: %lf walk_dist: %lf\n", wall_dist, c->walk_dist);
	if (c->walk_dist > wall_dist - WALL_BUFF)
	{
		c->walk_dist =  wall_dist - WALL_BUFF;
		if (key_code == W_KEY || key_code == S_KEY)
		{
			c->x_walk = fabs(cos(c->pdir)) * c->walk_dist;
			c->y_walk = fabs(sin(c->pdir)) * c->walk_dist;
		}
		else if (key_code == A_KEY || key_code == D_KEY)
		{
			c->x_walk = fabs(sin(c->pdir)) * c->walk_dist;
			c->y_walk = fabs(cos(c->pdir)) * c->walk_dist;
		}
	}
	if (c->run_dist > wall_dist - WALL_BUFF)
	{
		c->run_dist = wall_dist - WALL_BUFF;
		if (key_code == W_KEY || key_code == S_KEY)
		{
			c->x_walk = fabs(cos(c->pdir)) * c->run_dist;
			c->y_walk = fabs(sin(c->pdir)) * c->run_dist;
		}
		else if (key_code == A_KEY || key_code == D_KEY)
		{
			c->x_walk = fabs(sin(c->pdir)) * c->run_dist;
			c->y_walk = fabs(cos(c->pdir)) * c->run_dist;
		}
	}
}

