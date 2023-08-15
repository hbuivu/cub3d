/* NOTES:
-what happens when you hit a corner?
*/
#include "../include/cub3D.h"

//bc there are inconsistencies with floats, this will get the approx value of float
int	ch_num(double angle, double comp)
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
	if (ch_num(main->calc->angle, main->n_angle) || ch_num(main->calc->angle, main->s_angle))
		main->calc->stepx = 0;
	else if (main->calc->angle < main->n_angle || main->calc->angle > main->s_angle)
		main->calc->stepx = 1;
	else if (main->calc->angle > main->n_angle && main->calc->angle < main->s_angle)
		main->calc->stepx = -1;
	if (ch_num(main->calc->angle, 0) || ch_num(main->calc->angle, M_PI) || ch_num(main->calc->angle, main->e_angle))
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
		main->calc->pdir = main->w_angle;
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

int	rgb_to_int(int *rgb)
{
	int	red;
	int	green;
	int	blue;

	red = rgb[0];
	green = rgb[1];
	blue = rgb[2];
	return (red << 16 | green << 8 | blue);
}

void	draw_floor_ceiling(t_main *main)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	// draw ceiling (top half of window)
	while (row < main->win_height/2)
	{
		while (col < main->win_width)
		{
			ft_pixel_put(&main->img, col, row, rgb_to_int(main->c_color));
			col++;
		}
		col = 0;
		row++;
	}
	while (row < main->win_height)
	{
		while (col < main->win_width)
		{
			ft_pixel_put(&main->img, col, row, rgb_to_int(main->f_color));
			col++;
		}
		col = 0;
		row++;
	}
	// printf("c_color: %i, %i, %i\n", main->c_color[0], main->c_color[1], main->c_color[2]);
	// printf("f_color: %i, %i, %i\n", main->f_color[0], main->f_color[1], main->f_color[2]);
	// printf("f: %i\n", rgb_to_int(main->f_color));
	// printf("c: %i\n", rgb_to_int(main->c_color));
}
/* for wall colors, if moving along column, can check for east and west colors
if moving along row, can check for north/south colors */
void	draw_wall(int x, t_main *main)
{
	double	start;
	double	stop;
	double	mid;
	double	half_wall;
	int		color;

	mid = main->calc->pln_height / 2;
	half_wall = main->calc->wall_height / 2;
	start = round(mid - half_wall);
	if (start < 0)
		start = 0;
	stop = round(mid + half_wall);
	if (stop >= main->calc->pln_height)
		stop = main->calc->pln_height - 1;
	// if (x == 672)
	// 	color = 16737380; //pink
	if (main->calc->wall_face == NORTH)
		color = 16711680; //RED
	else if (main->calc->wall_face == SOUTH)
		color = 65280; //GREEN
	else if (main->calc->wall_face == EAST)
		color = 255; //BLUE
	else if (main->calc->wall_face == WEST)
		color = 6553700; //PURPLE
	while (start <= stop)
	{
		ft_pixel_put(&main->img, x, (int)start, color);
		start++;
	}
}

int	check_coord(int jump, t_main *main)
{
	int		row;
	int		col;
	t_calc	*c;

	c = main->calc;
	if (jump == COL)
	{
		row = c->col_inty / c->upg;
		if (c->stepx == -1)
			col = (c->col_int / c->upg) - 1;
		else
			col = c->col_int / c->upg;
		if (c->col_inty > 0 && c->col_int > 0 && row < main->map_height &&
			col < main->map_width && main->map[row][col] != '1')
			return (1);
	}
	else if (jump == ROW)
	{
		col = c->row_intx / c->upg;
		if (c->stepy == -1)
			row = (c->row_int / c->upg) - 1;
		else
			row = c->row_int / c->upg;
		if (c->row_intx > 0 && c->row_int > 0 && row < main->map_height &&
			col < main->map_width && main->map[row][col] != '1')
			return (1);
	}
	return (0);
}

void	cast_hline(t_calc *c, t_main *main)
{
	c->deltay = 0;
	c->deltax = 64;
	if (c->stepx == 1)
	{
		c->wall_face = WEST;
		c->col_int = round_up(c->px / c->upg) * c->upg;
	}
	else if (c->stepx == -1)
	{
		c->wall_face = EAST;
		// c->col_int = round_down(c->px / c->upg) * c->upg - 1;
		c->col_int = round_down(c->px / c->upg) * c->upg;

	}
	c->col_inty = c->py;
		// printf("***BEGINNING***\n");
		// 	printf("c->col_inty: %lf\n", c->col_inty);
		// 	printf("c->col_int: %lf\n", c->col_int);
		// 	printf("COL: check row: %i check column: %i\n", (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		// 	printf("deltax: %lf\n", c->deltax);
	// while (c->col_inty > 0 && c->col_int > 0 &&
	// 	(int)(c->col_inty / c->upg) < main->map_height &&
	// 	(int)(c->col_int / c->upg) < main->map_width &&
	// 	(main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1'))
	while (check_coord(COL, main))
	{
		c->col_int += c->stepx * c->deltax;
		// printf("col_int: %lf\n", c->col_int);
	}
	c->cor_dist = fabs(c->col_int - c->px);
	// printf("cor_dist: %lf\n", c->cor_dist);
}

void	cast_vline(t_calc *c, t_main *main)
{
	c->deltay = 64;
	c->deltax = 0;
	if (c->stepy == 1)
	{
		c->wall_face = NORTH;
		c->row_int = round_up(c->py / c->upg) * c->upg;
	}
	else if (c->stepy == -1)
	{
		c->wall_face = SOUTH;
		// c->row_int = round_down(c->py / c->upg) * c->upg - 1;
		c->row_int = round_down(c->py / c->upg) * c->upg;
	}
	c->row_intx = c->px;
	// while (c->row_int > 0 && c->row_intx > 0 &&
	// 	(int)(c->row_int / c->upg) < main->map_height &&
	// 	(int)(c->row_intx / c->upg) < main->map_width &&
	// 	main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)] != '1')
	while (check_coord(ROW, main))
		c->row_int += c->stepy * c->deltay;
	c->cor_dist = fabs(c->row_int - c->py);

}

//NOTE: create a variable for tan of angle so it only has to be calculated once
void	cast_line(int x, t_calc *c, t_main *main)
{
	c->deltay = fabs(c->upg * tan(c->angle));
	c->deltax = fabs(c->upg / tan(c->angle));
	if (c->stepx == 1)
		c->col_int = round_up(c->px / c->upg) * c->upg;
	else if (c->stepx == -1)
		// c->col_int = round_down(c->px / c->upg) * c->upg - 1;
		// the -1 creates lines bc it takes the ray one step further than it ought to, this sometimes causes it to check the wrong grid
		c->col_int = round_down(c->px / c->upg) * c->upg;
	c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * tan(c->angle)));

	if (c->stepy == 1)
		c->row_int = round_up(c->py / c->upg) * c->upg;
	else if (c->stepy == -1)
		// c->row_int = round_down(c->py / c->upg) * c->upg - 1; //could have same issue here
		c->row_int = round_down(c->py / c->upg) * c->upg; //could have same issue here
	c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / tan(c->angle)));

	// if (x == 672)
	// {
		// printf("***BEGINNING***\n");
		// 	printf("c->col_inty: %lf\n", c->col_inty);
		// 	printf("c->col_int: %lf\n", c->col_int);
		// 	printf("COL: %i: check row: %i check column: %i\n", x, (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		// 	printf("c->row_int: %lf\n", c->row_int);
		// 	printf("c->row_intx: %lf\n", c->row_intx);
		// 	printf("ROW: %i: check row: %i check column: %i\n", x, (int)(c->row_int / c->upg), (int)(c->row_intx / c->upg));
		// 	printf("deltay: %lf\n", c->deltay);
		// 	printf("deltax: %lf\n", c->deltax);
		// printf("\n***COLUMN JUMPS***\n");
	// }
	//have a check_map function here;
	/* basically, if stepx/y is negative, we need to check 1 after the rounding */
	// while (c->col_inty > 0 && c->col_int > 0 &&
	// 	(int)(c->col_inty / c->upg) < main->map_height &&
	// 	(int)(c->col_int / c->upg) < main->map_width &&
	// 	(main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1'))
	while (check_coord(COL, main))
	{
		c->col_int += c->stepx * c->upg;
		c->col_inty += c->stepy * c->deltay;
		// if (x == 672)
		// {
		// 	printf("deltay: %lf\n", c->deltay);
		// 	printf("c->col_inty: %lf\n", c->col_inty);
		// 	printf("c->col_int: %lf\n", c->col_int);
		// 	printf("check row: %i check column: %i\n", (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		// }
	}
	// if (x == 672)
	// 	printf("\n***ROW JUMPS***\n");
	// while (c->row_int > 0 && c->row_intx > 0 &&
	// 	(int)(c->row_int / c->upg) < main->map_height &&
	// 	(int)(c->row_intx / c->upg) < main->map_width &&
	// 	main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)] != '1')
	while (check_coord(ROW, main))
	{
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
		// if (x == 672)
		// {
		// 	printf("deltax: %lf\n", c->deltax);
		// 	printf("c->row_intx: %lf\n", c->row_intx);
		// 	printf("c->row_int: %lf\n", c->row_int);
		// 	printf("check row: %i check column: %i\n", (int)(c->row_int/ c->upg), (int)(c->row_intx / c->upg));
		// }
	}
	//NOTE:here, if one direction goes out of bounds, we should ignore it
	//NOTE:also no need to compare distances if the angle is perpendicular
	//find the point that is the shortest distance from original px and py
	c->dist_col = fabs((c->px - c->col_int) / cos(c->angle));
	c->dist_row = fabs((c->px - c->row_intx) / cos(c->angle));
	if (c->dist_col <= c->dist_row)
	{
		// printf("\nUsing dist_col\n");
		c->cor_dist = c->dist_col * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		if (c->stepx == 1)
			c->wall_face = WEST;
		else if (c->stepx == -1)
			c->wall_face = EAST;
	}
	else
	{
		// printf("\nUsing dist_row\n");
		c->cor_dist = c->dist_row * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		if (c->stepy == 1)
			c->wall_face = NORTH;
		else if (c->stepy == -1)
			c->wall_face = SOUTH;
	}
}

void	raycast(t_main *main)
{
	t_calc	*c;
	int		x;

	c = main->calc;
	x = 0;
	draw_floor_ceiling(main);
	// printf("pdir: %lf\n", c->pdir);
	// printf("angle_incr: %lf\n", c->ray_incr);
	// printf("px: %lf py: %lf\n", c->px, c->py);
	while (x < main->calc->pln_width)
	{
		// printf("x is: %i\n", x);
		// // if (x == 805 || x == 1147 || x == 1148 || x == 1149)
		// printf("angle: %lf\n", c->angle);
		if (ch_num(c->angle, 0) || ch_num(c->angle, main->w_angle) || ch_num(c->angle, main->e_angle))
		{
			// printf("casting horizontal line\n");
			cast_hline(c, main);
		}
		else if (ch_num (c->angle, main->n_angle) || ch_num(c->angle, main->s_angle))
			cast_vline(c, main);
		else
			cast_line(x, c, main);

		c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;
		// if (x == 672)
		// {
		// 	printf("COL: check row: %i check column: %i\n", (int)(c->col_inty / c->upg), (int)(c->col_int / c->upg));
		// 	printf("ROW: check row: %i check column: %i\n", (int)(c->row_int / c->upg), (int)(c->row_intx / c->upg));
		// 	printf("dist_col: %lf\n", c->dist_col);
		// 	printf("dist_row: %lf\n", c->dist_row);
		// 	printf("cor_dist: %lf\n", c->cor_dist);
		// 	printf("wall_height: %lf\n", c->wall_height);
		// }

		draw_wall(x, main);
		x++;
		recalc(main);
	}
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
	mlx_key_hook(main->mlx.mlx_win, ft_movement, main);
	mlx_hook(main->mlx.mlx_win, 17, 1L << 17, ft_close, main);
	mlx_loop(main->mlx.mlx_ptr);
}
