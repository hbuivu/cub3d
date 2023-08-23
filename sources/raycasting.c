/* NOTES:
-what happens when you hit a corner?
*/
#include "../include/cub3D.h"

void	cast_hline(t_calc *c, t_main *main)
{
	c->deltay = 0;
	c->deltax = 64;
	if (c->stepx == 1)
	{
		c->wall_face = main->img_we_wall;
		c->col_int = ceil(c->px / c->upg) * c->upg;
	}
	else if (c->stepx == -1)
	{
		c->wall_face = main->img_ea_wall;
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
		c->wall_face = main->img_no_wall;
		c->row_int = ceil(c->py / c->upg) * c->upg;
	}
	else if (c->stepy == -1)
	{
		c->wall_face = main->img_so_wall;
		c->row_int = floor(c->py / c->upg) * c->upg;
	}
	c->row_intx = c->px;
	while (check_coord(ROW, main))
		c->row_int += c->stepy * c->deltay;
	c->cor_dist = fabs(c->row_int - c->py);
	c->wall_slice = (int)c->row_intx % 64;

}

void	calc_intercepts(t_calc *c, t_main *main)
{
	c->deltay = fabs(c->upg * c->tan_angle);
	c->deltax = fabs(c->upg / c->tan_angle);
	if (c->stepx == 1)
		c->col_int = ceil(c->px / c->upg) * c->upg;
	else if (c->stepx == -1)
		c->col_int = floor(c->px / c->upg) * c->upg;
	c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * c->tan_angle));
	if (c->stepy == 1)
		c->row_int = ceil(c->py / c->upg) * c->upg;
	else if (c->stepy == -1)
		c->row_int = floor(c->py / c->upg) * c->upg;
	c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / c->tan_angle));
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
}

void	cast_line(int x, t_calc *c, t_main *main)
{
	calc_intercepts(c, main);
	c->dist_col = fabs((c->px - c->col_int) / cos(c->angle));
	c->dist_row = fabs((c->px - c->row_intx) / cos(c->angle));
	if (c->dist_col <= c->dist_row)
	{
		c->wall_slice = (int)c->col_inty % 64;
		c->cor_dist = c->dist_col * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		if (c->stepx == 1)
			c->wall_face = main->img_we_wall;
		else if (c->stepx == -1)
			c->wall_face = main->img_ea_wall;
	}
	else
	{
		c->wall_slice = (int)c->row_intx % 64;
		c->cor_dist = c->dist_row * cos((c->fov - (2 * x * c->ray_incr)) / 2);
		if (c->stepy == 1)
			c->wall_face = main->img_no_wall;
		else if (c->stepy == -1)
			c->wall_face = main->img_so_wall;
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
		else if (ch_num(c->angle, c->rad_90) || ch_num(c->angle, c->rad_270))
			cast_vline(c, main);
		else
			cast_line(x, c, main);
		c->wall_height = (c->upg / c->cor_dist) * c->pln_dist;
		draw_wall(x, main);
		x++;
		recalc(main);
	}
	mlx_put_image_to_window(main->mlx.mlx_ptr, main->mlx.mlx_win, main->img.img, 0, 0);
	// mlx_key_hook(main->mlx.mlx_win, key_press, main);
	mlx_hook(main->mlx.mlx_win, 2, 1L << 0, key_press, main);
	// mlx_hook(main->mlx.mlx_win, 17, 1L<<17, ft_close, &main->mlx);
	mlx_hook(main->mlx.mlx_win, 17, 1L << 17, ft_close, main);
	mlx_hook(main->mlx.mlx_win, 06, 1L << 6, mouse_move, main);
	mlx_loop(main->mlx.mlx_ptr);
}

int	mouse_move(int x, int y, t_main *main)
{
	if (y != -1)
		main->calc->angle += (x - main->mouse_x) / 3;
	main->mouse_x = x;
	return (0);
}

// 	mlx_hook(cub->s_mlx.win, 3, 1L << 1, key_release, (void *)cub);
// 	mlx_loop_hook(cub->s_mlx.mlx, action_loop, (void *)cub);
