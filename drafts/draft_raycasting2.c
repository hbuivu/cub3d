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
	main->calc = (t_calc *)cub_calloc(1, sizeof(t_calc), main);
	main->calc->upg = 64;
	main->calc->fov = 66;
	main->calc->rfov = main->calc->fov * (M_PI / 180);
	main->calc->pln_width = main->win_width;
	main->calc->pln_height = main->win_height;
	main->calc->pln_dist = (main->calc->pln_width / 2) / tan(main->calc->rfov / 2);
	main->calc->px = (((double)main->player_pos[0] + .5) * main->calc->upg);
	main->calc->py = (((double)main->player_pos[1] + .5) * main->calc->upg);
	if (main->player_dir == 'E')
		main->calc->pdir = 0;
	else if (main->player_dir == 'N')
		main->calc->pdir = 90;
	else if (main->player_dir == 'W')
		main->calc->pdir = 180;
	else if (main->player_dir == 'S')
		main->calc->pdir = 270;
	main->calc->ray_incr = main->calc->fov / main->calc->pln_width;
	main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
	main->calc->rangle = main->calc->angle * (M_PI / 180);
	if (main->calc->angle < 0)
		main->calc->angle += 360;
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

void	draw_wall(int x, t_main *main)
{
	float	start;
	float	stop;
	float	mid;
	float	half_wall;

	mid = main->calc->pln_height / 2;
	half_wall = main->calc->wall_height;

	start = round(mid - half_wall);
	if (start < 0)
		start = 0;
	stop = round(mid + half_wall);
	if (stop > main->calc->wall_height)
		stop = main->calc->wall_height;
	while (start <= stop)
	{
		ft_pixel_put(main->img->img, x, (int)start, 3093132);
		start++;
	}
}

void	raycast(t_main *main)
{
	t_calc	*c;
	
	c = main->calc;
	
	//find deltax and deltay (use deltay with col, and deltax with row)
	//the ray moves for deltay each time it jumps one column
	//the ray moves for deltax each time it jumps one row
	c->deltax = fabs(c->upg / tan(c->rangle));
	c->deltay = fabs(c->upg * tan(c->rangle));

	//find first column intersection from starting position
	// for cstepx/cstepy== -1. we subtract 1 so it takes us into the column to the left of us when we check. otherwise we are stuck in the our current box
	if (c->stepx == 1)
		c->col_int = round_up(c->px / c->upg) * c->upg;
	else if (c->stepx == -1)
		c->col_int = round_down(c->px / c->upg) * c->upg - 1; 
	c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * tan(c->rangle)));

	//find first row intersection from starting position
	if (c->stepy == 1)
		c->row_int = round_up(c->py / c->upg) * c->upg;
	else if (c->stepy == -1)
		c->row_int = round_down(c->py / c->upg) * c->upg - 1;
	c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / tan(c->rangle)));
	
	// check for a wall jumping columns
	printf("starting with: \n");
	printf("col_int: %lf\n", c->col_int);
	printf("col_inty: %lf\n", c->col_inty);
	printf("check row (col_inty): %i\n", (int)(c->col_inty / c->upg));
	printf("check col (col_int): %i\n", (int)(c->col_int / c->upg));
	while (main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1')
	{
		c->col_int += c->stepx * c->upg;
		c->col_inty += c->stepy * c->deltay;
	}
	printf("ending with: \n");
	printf("col_int: %lf\n", c->col_int);
	printf("col_inty: %lf\n", c->col_inty);
	printf("check row (col_inty): %i\n", (int)(c->col_inty / c->upg));
	printf("check col (col_int): %i\n", (int)(c->col_int / c->upg));

	//check for a wall jumping rows
	printf("starting with: \n");
	printf("row_int: %lf\n", c->row_int);
	printf("row_intx: %lf\n", c->row_intx);
	printf("check row (row_int): %i\n", (int)(c->row_int / c->upg));
	printf("check col (row_intx): %i\n", (int)(c->row_intx / c->upg));
	while (main->map[(int)(c->row_int / c->upg)][(int)(c->row_int / c->upg)] != '1')
	{
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
	}
	printf("ending with: \n");
	printf("row_int: %lf\n", c->row_int);
	printf("row_intx: %lf\n", c->row_intx);
	printf("check row (row_int): %i\n", (int)(c->row_int / c->upg));
	printf("check col (row_intx): %i\n", (int)(c->row_intx / c->upg));

	//find the point that is the shortest distance from original px and py
	c->dist_col = fabs((c->px - c->col_int) / cos(c->rangle));
	printf("dist_col: %lf\n", c->dist_col);
	c->dist_row = fabs((c->px - c->row_intx) / cos(c->rangle));
	printf("dist_row: %lf\n", c->dist_row);
	
	//calculate the "corrected" distance to wall
	if (c->dist_col <= c->dist_row)
		c->cor_dist = c->dist_col * cos(c->rfov / 2);
	else
		c->cor_dist = c->dist_row * cos(c->rfov / 2);
	printf("cor_dist: %lf\n", c->cor_dist);

	//calculate wall height at that point
	// ratio of actual wall height / actual distance from wall  = projected wall height / player distance from projection plane
	c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;

	//draw the wall
	//get x here;
	draw_wall(x, main);
	x++;

}	





// c->dist_col = ((c->px - c->col_int) * (c->px - c->col_int)) + ((c->py - c->col_inty)*(c->py - c->col_inty));
// c->dist_row = ((c->px - c->row_intx) * (c->px - c->row_intx)) + ((c->py - c->row_int)*(c->py - c->row_int));