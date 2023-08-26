/* For sheer walls
1. Send two rays
	going out to the very edge
	back to the players position
2. for every wall hit, record in a node
	wall slice
	face
	distance from player
	ray 1 or 2 (1 is from player to edge, 2 is from edge to player)
3. append node to a linked list
4. sort linked list by distance from player, largest to smallest
	in the event that both distances are the same, sort ray 2 first then ray 1 
5. draw wall iterating through linked list front to back */

#include "../include/cub3D.h"

void	record_wall_info(int x, int jump, t_main *main)
{
	t_wall	*node;
	t_calc	*c;

	c = main->calc;
	node = (t_wall *)cub_calloc(1, sizeof(t_wall), main);
	node->ray = c->ray;
	if (jump == COL)
	{
		node->dist = fabs((c->px - c->col_int) / cos(c->angle));
		node->wall_slice = (int)c->col_inty % 64;
		if (c->stepx == 1)
			node->wall_face = main->img_we_wall;
		else
			node->wall_face = main->img_ea_wall;
	}
	else if (jump == ROW)
	{
		node->dist = fabs((c->py - c->row_int) / sin(c->angle));
		node->wall_slice = (int)c->col_inty % 64;
		if (c->stepy == 1)
			node->wall_face = main->img_no_wall;
		else if (c->stepy == -1)
			node->wall_face = main->img_so_wall;
	}
	node->cor_dist = node->dist * fabs(cos((c->fov - (2 * x * c->ray_incr)) / 2));
	node->wall_height = (c->upg / c->cor_dist) * c->pln_dist;
	node->start = (int)(round((c->pln_height / 2) - (node->wall_height / 2)));
	node->end =  (int)(round(node->start + node->wall_height));
	if (node->end > c->pln_height || ch_num(node->end, c->pln_height))
		node->stop = c->pln_height - 1;
	if (c->wall_list == NULL)
		c->wall_list = node;
	else 
	{
		node->prev = c->wall_list_cur;
		c->wall_list_cur->next = node;
	}
	c->wall_list_cur = node;
}

void	calc_delta(t_main *main)
{
	t_calc *c;

	c = main->calc;
	if (ch_num(c->angle, 0) || ch_num(c->angle, M_PI))
	{
		c->deltay = 0;
		c->deltax = 64;
	}
	else if (ch_num(c->angle, c->rad_90) || ch_num(c->angle, c->rad_270))
	{
		c->deltay = 64;
		c->deltax = 0;
	}
	else
	{
		c->deltay = fabs(c->upg * c->tan_angle);
		c->deltax = fabs(c->upg / c->tan_angle);
	}
}


void	calc_intercepts(t_main *main)
{
	t_calc *c;

	c = main->calc;
	if (c->stepx == 1)
		c->col_int = ceil(c->px / c->upg) * c->upg;
	else if (c->stepx == -1)
		c->col_int = floor(c->px / c->upg) * c->upg;
	if (ch_num(c->angle, 0) || ch_num(c->angle, M_PI))
		c->col_inty = c->py;
	else
		c->col_inty = c->py + (c->stepy * fabs((c->col_int - c->px) * c->tan_angle));
	if (c->stepy == 1)
		c->row_int = ceil(c->py / c->upg) * c->upg;
	else if (c->stepy == -1)
		c->row_int = floor(c->py / c->upg) * c->upg;
	if (ch_num(c->angle, c->rad_90) || ch_num(c->angle, c->rad_270))
		c->row_intx = c->px;
	else
		c->row_intx = c->px + (c->stepx * fabs((c->row_int - c->py) / c->tan_angle));
}

void	sort_wall_list(t_main *main)
{
	t_wall *w;
	t_wall	*temp;

	w = main->calc->wall_list;
	while (w)
	{
		if (w->dist > w->next->dist || 
			(w->dist == w->next->dist && w->ray < w->next->ray))
		{
			temp = w->next;
			w->next->prev = w->prev;
			if (w->prev)
				w->prev->next = w->next;
			w->prev = w->next;
			w->next = w->next->next;
			temp->next->prev = w;
			temp->next = w;
			w = main->calc->wall_list;
		}
		else
			w = w->next;
	}
}

void	free_wall_list(t_main *main)
{
	t_wall *w;
	t_wall	*cur;

	w = main->calc->wall_list;
	cur = w;
	while (cur)
	{
		w = w->next;
		free(cur);
		cur = w;
	}
}

void	cast_line(int x, t_main *main)
{
	t_calc *c;

	c = main->calc;
	calc_delta(main);
	calc_intercepts(main);
	c->ray = 1;
	//calc all wall hits for columns
	while (c->col_int >= 0  && c->col_int < WIN_WIDTH &&
		!ch_num(c->angle, c->rad_90) && !ch_num(c->angle, c->rad_270))
	{
		if (check_coord(COL, main) == 0)
			record_wall_info(x, COL, main);
		c->col_int += c->stepx * c->upg;
		c->col_inty += c->stepy * c->deltay;
	}
	//calculate all wall hits for rows
	while (c->row_int >= 0 && c->row_int < WIN_HEIGHT &&
		!ch_num(c->angle, 0) && !ch_num(c->angle, M_PI))
	{
		if (check_coord(ROW, main) == 0)
			record_wall_info(x, ROW, main);
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
	}
	//take column and row back into bounds of the map
	if (c->col_int < 0 || c->col_int > WIN_WIDTH || ch_num(c->col_int, WIN_WIDTH))
	{
		c->col_int -= c->stepx * c->upg;
		c->col_inty -= c->stepy * c->deltay;
	}
	if (c->row_int < 0 || c->row_int > WIN_HEIGHT || ch_num(c->row_int, WIN_HEIGHT))
	{
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
	}
}

void	cast_back_line(int x, t_main *main)
{
	t_calc *c;

	c = main->calc;
	c->ray = 2;
	c->deltax *= -1;
	c->deltay *= -1;
	while (c->col_int > c->px &&
		!ch_num(c->angle, c->rad_90) && !ch_num(c->angle, c->rad_270))
	{
		if (check_coord(COL, main) == 0)
			record_wall_info(x, COL, main);
		c->col_int += c->stepx * c->upg;
		c->col_inty += c->stepy * c->deltay;
	}
	while (c->row_int > c->py &&
		!ch_num(c->angle, 0) && !ch_num(c->angle, M_PI))
	{
		if (check_coord(ROW, main) == 0)
			record_wall_info(x, ROW, main);
		c->row_int += c->stepy * c->upg;
		c->row_intx += c->stepx * c->deltax;
	}
}

void	draw_wall_list(int x, t_main *main)
{
	t_calc *c;
	t_wall	*w;
	t_point	p;
	int		y;

	w = main->calc->wall_list;
	c = main->calc;
	while (w)
	{
		y = 0;
		p.scale = w->wall_height / c->upg;
		p.orig_x = w->wall_slice;
		while (y < (int)w->wall_height && w->start <= w->end)
		{
			if (w->start >= 0)
			{
				p.orig_y = y / p.scale;
				get_nearest_pix(&p, main);
				interpolate(x, w->start, &p, main);
			}
			y++;
			w->start++;
		}
		w = w->next;
	}
}

void	double_raycast(t_main *main)
{
	t_calc	*c;
	int		x;

	c = main->calc;
	x = 0;
	draw_floor_ceiling(main);
	while (x < main->calc->pln_width)
	{
		cast_line(x, c, main);
		cast_back_line(x, c, main);
		sort_wall_list(main);
		draw_wall_list(main);
		x++;
		recalc(main);
		//free wall_list
		//set wall_list and wall_list cur back to null
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

// t_wall	*cast_hline(t_calc *c, t_main *main)
// {
// 	t_wall	*wall_info;
// 	t_wall	*node;
// 	t_wall	*cur;
	
	
// 	wall_info = NULL;
// 	if (c->stepx == 1)
// 		c->col_int = ceil(c->px / c->upg) * c->upg;
// 	else if (c->stepx == -1)
// 		c->col_int = floor(c->px / c->upg) * c->upg;
	
// 	while (c->px >= 0 && c->px < WIN_WIDTH)
// 	{
// 		if (check_coord(COL, main) == 0)
// 		{
// 			node = record_wall_info(COL, main);
// 			if (wall_info == NULL)
// 				wall_info = node;
// 			else
// 				cur->next = node;
// 			cur = node;
// 		}
// 		c->col_int += c->stepx * c->deltax;
// 	}
// }

// void	cast_vline(t_calc *c, t_main *main)
// {
// 	t_wall	*wall_info;
// 	t_wall	*node;
// 	t_wall	*cur;

	
// 	wall_info = NULL;
// 	if (c->stepy == 1)
// 		c->row_int = ceil(c->py / c->upg) * c->upg;
// 	else if (c->stepy == -1)
// 		c->row_int = floor(c->py / c->upg) * c->upg;
// 	c->row_intx = c->px;
// 	while (c->p >= 0 && c->py < )
// 	{

// 	}
// 		c->row_int += c->stepy * c->deltay;
// 	c->cor_dist = fabs(c->row_int - c->py);
// 	c->wall_slice = (int)c->row_intx % 64;

// }

// if (ch_num(c->angle, 0) || ch_num(c->angle, M_PI))
// 	{
// 		c->dist_col = fabs(c->px - c->col_int);
// 		c->dist_row = 0;
// 	}
// 	else if (ch_num(c->angle, c->rad_90) || ch_num(c->angle, c->rad_270))
// 	{
// 		c->dist_row = fabs(c->py - c->row_int);
// 		c->dist_col = 0;
// 	}
// 	else
// 	{
// 		c->dist_row = fabs((c->px - c->col_int) / cos(c->angle));
// 		c->dist_col = fabs((c->py - c->row_int) / sin(c->angle));
// 	}
// 	if (c->dist_col < c->dist_row)
// 	{
// 		c->castback_px = c->col_int;
// 		c->castback_py = c->col_inty;
// 	}
// 	else
// 	{
// 		c->castback_py = c->row_int;
// 		c->castback_px = c->row_intx;
// 	}