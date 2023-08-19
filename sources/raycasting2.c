/* NOTES:
-what happens when you hit a corner?
*/
#include "../include/cub3D.h"

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

/* for wall colors, if moving along column, can check for east and west colors
if moving along row, can check for north/south colors */

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
		c->wall_face = main->img_we_wall; //WEST
		c->col_int = ceil(c->px / c->upg) * c->upg;
	}
	else if (c->stepx == -1)
	{
		c->wall_face = main->img_ea_wall; //EAST
		// c->col_int = floor(c->px / c->upg) * c->upg - 1; 
		c->col_int = floor(c->px / c->upg) * c->upg; 

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
		c->col_int += c->stepx * c->deltax;
	c->cor_dist = fabs(c->col_int - c->px);
	c->wall_slice = (int)c->col_inty % 64;
}

void	cast_vline(t_calc *c, t_main *main)
{
	c->deltay = 64;
	c->deltax = 0;
	if (c->stepy == 1)
	{
		c->wall_face = main->img_no_wall; //NORTH
		c->row_int = ceil(c->py / c->upg) * c->upg;
	}
	else if (c->stepy == -1)
	{
		c->wall_face = main->img_so_wall; //SOUTH
		// c->row_int = floor(c->py / c->upg) * c->upg - 1;
		c->row_int = floor(c->py / c->upg) * c->upg;
	}
	c->row_intx = c->px;
	// while (c->row_int > 0 && c->row_intx > 0 &&
	// 	(int)(c->row_int / c->upg) < main->map_height &&
	// 	(int)(c->row_intx / c->upg) < main->map_width &&
	// 	main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)] != '1')
	while (check_coord(ROW, main))
		c->row_int += c->stepy * c->deltay;
	c->cor_dist = fabs(c->row_int - c->py);
	c->wall_slice = (int)c->row_intx % 64;

}

//NOTE: create a variable for tan of angle so it only has to be calculated once
void	cast_line(int x, t_calc *c, t_main *main)
{
	c->deltay = fabs(c->upg * tan(c->angle));
	c->deltax = fabs(c->upg / tan(c->angle));
	if (c->stepx == 1)
		c->col_int = ceil(c->px / c->upg) * c->upg;
	else if (c->stepx == -1)
		// c->col_int = floor(c->px / c->upg) * c->upg - 1;
		// the -1 creates lines bc it takes the ray one step further than it ought to, this sometimes causes it to check the wrong grid
		c->col_int = floor(c->px / c->upg) * c->upg;
	c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * tan(c->angle)));

	if (c->stepy == 1)
		c->row_int = ceil(c->py / c->upg) * c->upg;
	else if (c->stepy == -1)
		// c->row_int = floor(c->py / c->upg) * c->upg - 1; //could have same issue here
		c->row_int = floor(c->py / c->upg) * c->upg; //could have same issue here
	c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / tan(c->angle)));

	/* basically, if stepx/y is negative, we need to check 1 after the rounding */
	// while (c->col_inty > 0 && c->col_int > 0 &&
	// 	(int)(c->col_inty / c->upg) < main->map_height &&
	// 	(int)(c->col_int / c->upg) < main->map_width &&
	// 	(main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1'))
	while (check_coord(COL, main))
	{
		c->col_int += c->stepx * c->upg;
		c->col_inty += c->stepy * c->deltay;
	}
	// while (c->row_int > 0 && c->row_intx > 0 &&
	// 	(int)(c->row_int / c->upg) < main->map_height &&
	// 	(int)(c->row_intx / c->upg) < main->map_width &&
	// 	main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)] != '1')
	while (check_coord(ROW, main))
	{
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
	}
	//NOTE:here, if one direction goes out of bounds, we should ignore it
	//NOTE:also no need to compare distances if the angle is perpendicular
	//find the point that is the shortest distance from original px and py
	c->dist_col = fabs((c->px - c->col_int) / cos(c->angle));
	c->dist_row = fabs((c->px - c->row_intx) / cos(c->angle));
	//what happens when dist_col == dist_row <- that is a hit at a corner most likely
	if (c->dist_col <= c->dist_row)
	{
		c->wall_slice = (int)c->col_inty % 64;
		c->cor_dist = c->dist_col * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		if (c->stepx == 1)
			c->wall_face = main->img_we_wall; //WEST
		else if (c->stepx == -1)
			c->wall_face = main->img_ea_wall; //EAST
	}
	else
	{
		c->wall_slice = (int)c->row_intx % 64;
		c->cor_dist = c->dist_row * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		if (c->stepy == 1)
			c->wall_face = main->img_no_wall; //NORTH
		else if (c->stepy == -1)
			c->wall_face = main->img_so_wall; //SOUTH
	}
}

void	raycast(t_main *main)
{
	t_calc	*c;
	int		x;

	c = main->calc;
	x = 0;
	draw_floor_ceiling(main);
	while (x < main->calc->pln_width)
	{
		if (ch_num(c->angle, 0) || ch_num(c->angle, main->angle.w_angle) || ch_num(c->angle, main->angle.e_angle))
			cast_hline(c, main);
		else if (ch_num(c->angle, main->angle.n_angle) || ch_num(c->angle, main->angle.s_angle))
			cast_vline(c, main);
		else
			cast_line(x, c, main);
		c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;
		draw_wall(x, main);
		x++;
		recalc(main);
	}
	
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
	
	// mlx_key_hook(main->mlx.mlx_win, ft_movement, main);
	// mlx_hook(main->mlx.mlx_win, 17, 1L << 17, ft_close, main);
	mlx_loop(main->mlx.mlx_ptr);
}
