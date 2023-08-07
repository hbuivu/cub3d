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
	if (main->calc->angle < 0)
		main->calc->angle += 360;
	main->calc->rangle = main->calc->angle * (M_PI / 180);
	calc_step(main);
}

void	recalc(t_main *main)
{
	main->calc->angle += main->calc->ray_incr;
	if (main->calc->angle < 0)
		main->calc->angle += 360;
	main->calc->rangle = main->calc->angle * (M_PI / 180);
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

	(void)x;
	mid = main->calc->pln_height / 2;
	half_wall = main->calc->wall_height;

	start = round(mid - half_wall);
	// printf("start: %i\n", (int)start);
	if (start < 0)
		start = 0;
	stop = round(mid + half_wall);
	// printf("stop: %i\n", (int)stop);
	if (stop > main->calc->pln_height)
		stop = main->calc->pln_height - 1;
	printf("x: %i start: %i stop: %i\n", x, (int)start, (int)stop);
	while (start <= stop)
	{
		ft_pixel_put(&main->img, x, (int)start, 3093132);
		start++;
	}
}

//if angle is horizontal
	//we would check each subsequent column keeping the same row
//if the angle is vertical
	//we would check each subsequent row keeping the same column
void	raycast(t_main *main)
{
	t_calc	*c;
	int		x;
	double	tolerance;
	
	c = main->calc;
	x = 0;
	tolerance = 0.000001;
	
	while (x < main->calc->pln_width)
	{
		printf("x: %i\n", x);
		printf("c->angle: %f", c->angle);
		printf("true or false: %i\n", fabs(c->angle - 270) < tolerance);
		//find deltax and deltay (use deltay with col, and deltax with row)
		//the ray moves for deltay each time it jumps one column
		//the ray moves for deltax each time it jumps one row
		if (fabs(c->angle - 0) < tolerance || fabs(c->angle - 180) < tolerance)
		{
			c->deltay = 0;
			c->deltax = 64;
			if (c->stepx == 1)
				c->col_int = round_up(c->px / c->upg) * c->upg;
			else if (c->stepx == -1)
				c->col_int = round_down(c->px / c->upg) * c->upg - 1; 
			c->col_inty = c->py;
		}
		else if (fabs(c->angle - 90) < tolerance || fabs(c->angle - 270) < tolerance)
		{
			printf("angle is 270\n");
			c->deltay = 64;
			c->deltax = 0;
			if (c->stepy == 1)
				c->row_int = round_up(c->py / c->upg) * c->upg;
			else if (c->stepy == -1)
				c->row_int = round_down(c->py / c->upg) * c->upg - 1;
			c->row_intx = c->px;
		}
		else
		{
			c->deltay = fabs(c->upg * tan(c->rangle));
			c->deltax = fabs(c->upg / tan(c->rangle));
			//find first column intersection from starting position
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
		}

		printf("check row: %i check column: %i\n", (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		// check for a wall jumping columns
		while ((int)(c->col_inty / c->upg) < main->map_height && (int)(c->col_int / c->upg) < main->map_width &&
			(main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1'))
		{
			c->col_int += c->stepx * c->upg;
			c->col_inty += c->stepy * c->deltay;
			printf("check row: %i check column: %i\n", (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		}

		//check for a wall jumping rows
		while (main->map[(int)(c->row_int / c->upg)][(int)(c->row_int / c->upg)] != '1')
		{
			c->row_int += c->stepy * c->upg;
			c->row_intx += c->stepx * c->deltax;
		}

		//find the point that is the shortest distance from original px and py
		c->dist_col = fabs((c->px - c->col_int) / cos(c->rangle));
		c->dist_row = fabs((c->px - c->row_intx) / cos(c->rangle));
	
		//calculate the "corrected" distance to wall
		if (c->dist_col <= c->dist_row)
			c->cor_dist = c->dist_col * cos(c->rfov / 2);
		else
			c->cor_dist = c->dist_row * cos(c->rfov / 2);

		//calculate wall height at that point
		// ratio of actual wall height / actual distance from wall  = projected wall height / player distance from projection plane
		c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;

		//draw the wall
		draw_wall(x, main);
		x++;
		recalc(main);
	}
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
}	





// c->dist_col = ((c->px - c->col_int) * (c->px - c->col_int)) + ((c->py - c->col_inty)*(c->py - c->col_inty));
// c->dist_row = ((c->px - c->row_intx) * (c->px - c->row_intx)) + ((c->py - c->row_int)*(c->py - c->row_int));