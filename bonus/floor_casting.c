#include "../include/cub3D.h"

#define PLAYER_HEIGHT 32

/* FLOOR CASTING
1. start from the furthest point and get true distance from straight distance
	starts from 5120 and ends at 10 (for now) 
		this will need to be interpolated too
2. find the rightmost pixel position and leftmost pixel position and insert pixel color
3. interpolate between the pixels to find every other world position and insert pixel color accordingly
4. do this for every single row */

void	draw_fl_text(t_floor *f, t_main *main)
{
	//convert world coordinates to tile coordinates
	f->pix_x = 
	f->pix_y = 
	//get color from image 
	//place color into (X, y coordinate of screen)
}
typedef struct s_floor
{
	double	perp_dist; //perpendicular distance from player to horizon
	double	true_dist; //the distance from player to a point on the horizon
	double	rx; //rightmost world x position of floor intersection
	double	ry; //rightmost world y position of floor intersection
	double	lx; //leftmost world x position of floor intersection
	double	ly; //leftmost world y position of floor intersection
	double	fx; // world x position in between rx and lx 
	double	fy; //world y position in between ry and ly
	double	pix_x; //x coordinate on image that corresponds to x floor position
	double	pix_y; //y coordinate on image that corresponds to y floor position
	double	dist_ratio; //plane distance * player_height - it is a constant variable for calculating the perpendicular distance
	int		hor_dist; //distance between horizon line and row
	double	w_ratio; //1 / win_width - 1
	double	xdist; //distance between rx and lx
	double	ydist; //distance between ry and ly
	int		x;
	int		y;
}	t_floor;

void	floor_casting(t_main *main)
{
	//make sure to reset numbers in calc first 
	t_floor	f;
	t_calc	*c;
	int	x;
	int	y;

	//precalculations
	f.dist_ratio = c->pln_dist * PLAYER_HEIGHT;
	//given that we are not going bigger with the screen, no need to check int max
	f.perp_dist = f.dist_ratio * 100; 
	f.hor_dist = 0;
	f.w_ratio = 1 / (WIN_WIDTH - 1);
	f.y = WIN_HEIGHT / 2;

	c = main->calc;
	while (f.y < WIN_HEIGHT)
	{
		//reset angle back to right
		c->angle = c->pdir - c->rel_angle;
		if (c->angle < 0)
			c->angle += c->rad_360;
		//find true distance
		f.true_dist = f.perp_dist / cos (c->rel_angle);
		//get right end pixel
		f.rx = c->px + (cos(c->angle) * f.true_dist);
		f.ry = c->py - (sin(c->angle) * f.true_dist);
		//change angle to leftmost angle
		c->angle += FOV;
		if (ch_num(c->angle, c->rad_360) || c->angle > c->rad_360)
			c->angle -= c->rad_360
		//get left end pixel
		f.lx = c->px + (cos(c->angle) * f.true_dist);
		f.ly = c->py + (cos(c->angle) * f.true_dist);
		//get distances between two points
		f.xdist = f.lx - f.rx;
		f.ydist = f.ly - f.ry; 
		//draw pixels into image
		f->fx = f.rx;
		f->fy = f.ry;
		draw_fl_text(&f, main);
		f->fx = f.lx;
		f->fx = f.ly;
		draw_fl_text(&f, main);
		//interpolate between left and right pixels to find positions and textures
		f.x = 0;

		while (f.x < WIN_WIDTH)
		{
			//t = x / (num_columns - 1);
			f.fx = f.rx + (x / WIN_WIDTH) * (f.lx - f.rx);
			f.fy = f.ry + (x / WIN_WIDTH) * (f.ly - f.ry);
			// t can be simplified
			//f.lx - f.rx, and same with y can just be calculated once
			draw_fl_text( main);
			f.x++;
		}
		//interpolate perp_dist
		f.hor_dist++;
		f.perp_dist = f.dist_ratio / f.hor_dist;
		//where r is the distance between the horizon and next row;
	}

}