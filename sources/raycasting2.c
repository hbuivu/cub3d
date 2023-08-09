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
		c->col_int = round_down(c->px / c->upg) * c->upg - 1; 
	}
	c->col_inty = c->py;
	while (c->col_inty > 0 && c->col_int > 0 &&
		(int)(c->col_inty / c->upg) < main->map_height && 
		(int)(c->col_int / c->upg) < main->map_width &&
		(main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1'))
		c->col_int += c->deltax;
	c->cor_dist = fabs(c->col_int - c->px);
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
		c->row_int = round_down(c->py / c->upg) * c->upg - 1;
	}
	c->row_intx = c->px;
	while (c->row_int > 0 && c->row_intx > 0 &&
		(int)(c->row_int / c->upg) < main->map_height &&
		(int)(c->row_intx / c->upg) < main->map_width &&
		main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)] != '1')
		c->row_int += c->deltay;
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
		c->col_int = round_down(c->px / c->upg) * c->upg - 1; 
	c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * tan(c->angle)));
	if (c->stepy == 1)
		c->row_int = round_up(c->py / c->upg) * c->upg;
	else if (c->stepy == -1)
		c->row_int = round_down(c->py / c->upg) * c->upg - 1;
	c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / tan(c->angle)));
	while (c->col_inty > 0 && c->col_int > 0 &&
		(int)(c->col_inty / c->upg) < main->map_height && 
		(int)(c->col_int / c->upg) < main->map_width &&
		(main->map[(int)(c->col_inty / c->upg)][(int)(c->col_int / c->upg)] != '1'))
	{
		c->col_int += c->stepx * c->upg;
		c->col_inty += c->stepy * c->deltay;
	}
	while (c->row_int > 0 && c->row_intx > 0 &&
		(int)(c->row_int / c->upg) < main->map_height &&
		(int)(c->row_intx / c->upg) < main->map_width &&
		main->map[(int)(c->row_int / c->upg)][(int)(c->row_intx / c->upg)] != '1')
	{
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
	}
	//NOTE:here, if one direction goes out of bounds, we should ignore it
	//NOTE:also no need to compare distances if the angle is perpendicular
	//find the point that is the shortest distance from original px and py
	c->dist_col = fabs((c->px - c->col_int) / cos(c->angle));
	c->dist_row = fabs((c->px - c->row_intx) / cos(c->angle));
	if (c->dist_col <= c->dist_row)
	{
		c->cor_dist = c->dist_col * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		if (c->stepx == 1)
			c->wall_face = WEST;
		else if (c->stepx == -1)
			c->wall_face = EAST;
	}	
	else
	{
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
	
	while (x < main->calc->pln_width)
	{
		if (ch_num(c->angle, 0) || ch_num(c->angle, main->w_angle) || ch_num(c->angle, main->e_angle))
			cast_hline(c, main);
		else if (ch_num (c->angle, main->n_angle) || ch_num(c->angle, main->s_angle))
			cast_vline(c, main);
		else
			cast_line(x, c, main);
		c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;
		draw_wall(x, main);
		x++;
		recalc(main);
	}
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
	mlx_key_hook(main->mlx.mlx_win, ft_movement, main);
	mlx_hook(main->mlx.mlx_win, 17, 1L << 17, ft_close, main);
	mlx_loop(main->mlx.mlx_ptr);
}	

