#include "../include/cub3D.h"

int	float_is(double angle, double comp)
{
	double	tolerance;

	tolerance = 0.000001;
	if (fabs(angle - comp) <= tolerance)
		return (1);
	return (0);
}

int	round_down(double num)
{
	return (num);
}

int	round_up(double num)
{
	return (num + 1);
}

void	calc_step(t_main *main)
{
	if (float_is(main->calc->angle, main->n_angle) || float_is(main->calc->angle, main->s_angle))
		main->calc->stepx = 0;
	else if (main->calc->angle < main->n_angle || main->calc->angle > main->s_angle)
		main->calc->stepx = 1;
	else if (main->calc->angle > main->n_angle && main->calc->angle < main->s_angle)
		main->calc->stepx = -1;
	if (float_is(main->calc->angle, 0) || float_is(main->calc->angle, M_PI) || float_is(main->calc->angle, main->e_angle))
		main->calc->stepy = 0;
	else if (main->calc->angle > 0 && main->calc->angle < M_PI)
		main->calc->stepy = -1;
	else if (main->calc->angle > M_PI && main->calc->angle < M_PI * 2)
		main->calc->stepy = 1;
}

void	init_calc(t_main *main)
{
	main->calc = (t_calc *)cub_calloc(1, sizeof(t_calc), main);
	main->calc->upg = 64;
	main->calc->fov = 66 * (M_PI / 180);
	main->calc->pln_width = main->win_width;
	main->calc->pln_height = main->win_height;
	main->calc->pln_dist = (main->calc->pln_width / 2) / tan(main->calc->fov / 2);
	main->calc->px = ((main->player_pos[0] + .5) * main->calc->upg);
	main->calc->py = ((main->player_pos[1] + .5) * main->calc->upg);
	if (main->player_dir == 'E')
		main->calc->pdir = 0;
	else if (main->player_dir == 'N')
		main->calc->pdir = main->n_angle;
	else if (main->player_dir == 'W')
		main->calc->pdir = M_PI;
	else if (main->player_dir == 'S')
		main->calc->pdir = main->s_angle;
	main->calc->ray_incr = main->calc->fov / main->calc->pln_width;
	main->calc->angle = main->calc->pdir - (main->calc->fov / 2);
	if (main->calc->angle < 0)
		main->calc->angle += 2 * M_PI;
	calc_step(main);
}

void	recalc(t_main *main)
{
	main->calc->angle += main->calc->ray_incr;
	if (main->calc->angle < 0)
		main->calc->angle += 2 * M_PI;
	else if (main->calc->angle > main->e_angle)
		main->calc->angle -= main->e_angle;
	calc_step(main);
}


void	draw_wall(int x, t_main *main)
{
	double	start;
	double	stop;
	double	mid;
	double	half_wall;

	mid = main->calc->pln_height / 2;
	half_wall = main->calc->wall_height / 2;
	start = round(mid - half_wall);
	if (start < 0)
		start = 0;
	stop = round(mid + half_wall);
	if (stop >= main->calc->pln_height)
		stop = main->calc->pln_height - 1;
	// printf("x: %i start: %i stop: %i\n", x, (int)start, (int)stop);
	if (x == 600)
	{
		while (start <= stop)
		{
			ft_pixel_put(&main->img, x, (int)start, 16711680);
			start++;
		}
	}
	else
	{
		while (start <= stop)
		{
			ft_pixel_put(&main->img, x, (int)start, 3093132);
			start++;
		}
	}
}

void	raycast(t_main *main)
{
	t_calc	*c;
	int		x;
	
	c = main->calc;
	x = 0;

	// (void)x;
	// (void)c;

	// print_calc(main);
	// printf("t or f: %i\n", float_is(6.283185, main->e_angle));
	
	while (x < main->calc->pln_width)
	{
		printf("\n");
		printf("x is: %i\n", x);
		printf("angle: %lf\n", main->calc->angle);
		printf("angle_incr: %lf\n", main->calc->ray_incr);
		//find deltax and deltay (use deltay with col, and deltax with row)
		//the ray moves for deltay each time it jumps one column
		//the ray moves for deltax each time it jumps one row
		if (float_is(c->angle, 0) || float_is(c->angle, M_PI) || float_is(c->angle, main->e_angle))
		{
			c->deltay = 0;
			c->deltax = 64;
			if (c->stepx == 1)
				c->col_int = round_up(c->px / c->upg) * c->upg;
			else if (c->stepx == -1)
				c->col_int = round_down(c->px / c->upg) * c->upg - 1; 
			c->col_inty = c->py;
		}
		else if (float_is (c->angle, main->n_angle) || float_is(c->angle, main->s_angle))
		{
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
			c->deltay = fabs(c->upg * tan(c->angle));
			c->deltax = fabs(c->upg / tan(c->angle));
			//find first column intersection from starting position
			if (c->stepx == 1)
				c->col_int = round_up(c->px / c->upg) * c->upg;
			else if (c->stepx == -1)
				c->col_int = round_down(c->px / c->upg) * c->upg - 1; 
			c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * tan(c->angle)));
			if (c->col_inty < 0)
				c->col_inty = 0;
			if (c->col_int < 0)
				c->col_int = 0;
			//find first row intersection from starting position
			if (c->stepy == 1)
				c->row_int = round_up(c->py / c->upg) * c->upg;
			else if (c->stepy == -1)
				c->row_int = round_down(c->py / c->upg) * c->upg - 1;
			c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / tan(c->angle)));
		}
		// printf("***BEGINNING***\n");
		// printf("c->col_inty: %lf\n", c->col_inty);
		// printf("c->col_int: %lf\n", c->col_int);
		// printf("COL: %i: check row: %i check column: %i\n", x, (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		// printf("c->row_int: %lf\n", c->row_int);
		// printf("c->row_intx: %lf\n", c->row_intx);
		// printf("ROW: %i: check row: %i check column: %i\n", x, (int)(c->row_int / c->upg), (int)(c->row_intx / c->upg));	
		// printf("deltay: %lf\n", c->deltay);
		// printf("deltax: %lf\n", c->deltax);
		// check for a wall jumping columns
		printf("\n***COLUMN JUMPS***\n");
		while (c->col_inty > 0 && c->col_int > 0 &&
			(int)(c->col_inty / c->upg) < main->map_height && 
			(int)(c->col_int / c->upg) < main->map_width &&
			(main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1'))
		{
			c->col_int += c->stepx * c->upg;
			c->col_inty += c->stepy * c->deltay;
			// printf("deltay: %lf\n", c->deltay);
			// printf("c->col_inty: %lf\n", c->col_inty);
			// printf("c->col_int: %lf\n", c->col_int);
			// printf("%i: check row: %i check column: %i\n", x, (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		}

		//check for a wall jumping rows
		printf("\n***ROW JUMPS***\n");
		// if (x == 625)
		// {
		// 	printf("c at row: %i col: %i: %c\n", (int)(c->row_int / c->upg), (int)(c->row_intx / c->upg), main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)]);
		// }
		while (c->row_int > 0 && c->row_intx > 0 &&
			(int)(c->row_int / c->upg) < main->map_height &&
			(int)(c->row_intx / c->upg) < main->map_width &&
			main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)] != '1')
		{
			c->row_int += c->stepy * c->upg;
			c->row_intx += c->stepx * c->deltax;
			// printf("deltax: %lf\n", c->deltax);
			// printf("c->row_intx: %lf\n", c->row_intx);
			// printf("c->row_int: %lf\n", c->row_int);
			// printf("%i: check row: %i check column: %i\n", x, (int)(c->row_int/ c->upg), (int)(c->row_intx / c->upg));
		}
		//NOTE:here, if one direction goes out of bounds, we should ignore it
		//NOTE:also no need to compare distances if the angle is perpendicular
		//find the point that is the shortest distance from original px and py
		c->dist_col = fabs((c->px - c->col_int) / cos(c->angle));
		c->dist_row = fabs((c->px - c->row_intx) / cos(c->angle));

		//calculate the "corrected" distance to wall
		if (c->dist_col <= c->dist_row)
		{
			printf("\nUsing dist_col\n");
			if (float_is(c->angle, 0) || float_is(c->angle, M_PI) || float_is(c->angle, main->e_angle))
				c->cor_dist = fabs(c->col_int - c->px);
			else
				c->cor_dist = c->dist_col * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		}
		else
		{
			printf("\nUsing dist_row\n");
			if (float_is(c->angle, main->n_angle) || float_is(c->angle, main->s_angle))
				c->cor_dist = fabs(c->row_int - c->py);
			else
				c->cor_dist = c->dist_row * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		}
		
		//calculate wall height at that point
		// ratio of actual wall height / actual distance from wall  = projected wall height / player distance from projection plane
		c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;
		printf("COL: check row: %i check column: %i\n", (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		printf("ROW: check row: %i check column: %i\n", (int)(c->row_int / c->upg), (int)(c->row_intx / c->upg));
		printf("dist_col: %lf\n", c->dist_col);
		printf("dist_row: %lf\n", c->dist_row);
		printf("cor_dist: %lf\n", c->cor_dist);
		printf("wall_height: %lf\n", c->wall_height);

		//draw the wall
		draw_wall(x, main);
		x++;
		recalc(main);
	}
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
}	


// int	rgb_to_int(int *rgb)
// {
// 	int	red;
// 	int	green;
// 	int	blue;

// 	red = rgb[0];
// 	green = rgb[1];
// 	blue = rgb[2];
// 	return (red << 16 | green << 8 | blue);
// }



// c->dist_col = ((c->px - c->col_int) * (c->px - c->col_int)) + ((c->py - c->col_inty)*(c->py - c->col_inty));
// c->dist_row = ((c->px - c->row_intx) * (c->px - c->row_intx)) + ((c->py - c->row_int)*(c->py - c->row_int));