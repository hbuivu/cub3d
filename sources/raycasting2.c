/* NOTES:
-what happens when you hit a corner?
*/
#include "../include/cub3D.h"


/* for wall colors, if moving along column, can check for east and west colors
if moving along row, can check for north/south colors */

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
		c->col_int = floor(c->px / c->upg) * c->upg; 

	}
	c->col_inty = c->py;
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
		c->col_int = floor(c->px / c->upg) * c->upg;
	c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * tan(c->angle)));

	if (c->stepy == 1)
		c->row_int = ceil(c->py / c->upg) * c->upg;
	else if (c->stepy == -1)
		// c->row_int = floor(c->py / c->upg) * c->upg - 1; //could have same issue here
		c->row_int = floor(c->py / c->upg) * c->upg; //could have same issue here
	c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / tan(c->angle)));
	while (check_coord(COL, main))
	{
		c->col_int += c->stepx * c->upg;
		c->col_inty += c->stepy * c->deltay;
	}
	while (check_coord(ROW, main))
	{
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
	}
	//NOTE:here, if one direction goes out of bounds, we should ignore it
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
		if (ch_num(c->angle, 0) || ch_num(c->angle, M_PI))
			cast_hline(c, main);
		else if (ch_num(c->angle, main->calc->rad_90) || ch_num(c->angle, main->calc->rad_270))
			cast_vline(c, main);
		else
			cast_line(x, c, main);
		c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;
		draw_wall(x, main);
		x++;
		recalc(main);
	}
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);	
}