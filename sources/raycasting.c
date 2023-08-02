/* 
N = (0, -1)
S = (0, 1)
E = (1, 0)
W = (-1, 0)
*/

#include "../include/cub3D.h"

void	raycasting(t_main *main)
{
	double	pl_x;
	double	pl_y;
	double	map_x;
	double	map_y;
	double	ray_x;
	double	ray_y;
	double	pl_dirx;
	double	pl_diry;
	double	camera_dirx;
	double	camera_diry;
	double	camera_mag;
	double	delta_x;
	double	delta_y;
	double	inter_x;
	double	inter_y;
	int		step_x;
	int		step_y;
	double	wall_dist;
	int		side;
	
	//set position of player in unit coordinates and map coordinates -> this would require conversion of everything else
	// pl_x = main->grid_size * main->player_pos[0] + (main->grid_size / 2);
	// pl_y = main->grid_size * main->player_pos[1] + (main->grid_size / 2);
	pl_x = main->player_pos[0] + .5;
	pl_y = main->player_pos[1] + .5;
	map_x = main->player_pos[0];
	map_y = main->player_pos[1];

	//set direction that player is facing (only direction, no magnitude, so it's in unit of 1)
	pl_dirx = main->player_vec[0];
	pl_diry = main->player_vec[1];

	//for the camera plane, we are working only in units of 1
	//set camera plane direction (only the direction, no magnitude, so it's in unit based on pl dir)
	//we set it to .65 since we want a FOV of 66 degrees. tan(33) = camera_dirx / 1 
	if (pl_dirx == 0)
		camera_dirx = .65; 
	else
		camera_dirx = 0;
	if (pl_diry == 0)
		camera_diry = .65;
	else
		camera_diry = 0;

	//get the magnitude of the camera plane <- still in units of 1
	//we have to send out rays for every x on the screen so the magnitude will shorten/lengthen camera plane
	int	x;
	x = 1;
	//here we set x = 1, but x spans the whole width of the window
	camera_mag = 2 * (x / main->win_width) - 1;

	//get ray in x and y components
	//ray = pl_dir + camera_dir * camera_mag
	ray_x = pl_dirx + camera_dirx * camera_mag;
	ray_y = pl_diry + camera_diry * camera_mag;

	//find delta x and delta y
	//delta x is the distance the vector travels per unit of x - going left and right col
	//delta y is the distance the vector travels per unit of y - going up and down rows
	//technically it should be delta_x = abs(|ray|/ray_x) and delta_y = abs(|ray|/ray_y);
	//however we are only interested in the ratio between delta x and delta y, so we simplify top number to 1
	if (ray_x != 0)
		delta_x = abs(1 / ray_x);
	else
		delta_x = 0;
	if (ray_y != 0)
		delta_y = abs(1 / ray_y);
	else
		delta_y = 0;

	//find the initial intersect at horizontal and vertical lines on map grid
	//the intersect will always give you a whole number
	//x indicates the column line that 
	if (ray_x < 0) //going left
	{
		step_x = -1;
		inter_x = (pl_x - map_x) + delta_x;
	}
	else //going right
	{
		step_x = 1;
		inter_x = (map_x + 1 - pl_x) + delta_x;
	}
	if (ray_y < 0) // going up
	{
		step_y = -1;
		inter_y = (pl_y - map_y) + delta_y;
	}
	else //going down
	{
		step_y = 1;
		inter_y = (map_y + 1 - pl_y) + delta_y
	}

	//travel through ray until we hit a wall
	while (/*we don't hit a wall*/)
	{
		if (inter_x < inter_y)
		{
			inter_x += delta_x;
			map_x += step_x;
			side = 0;
		}
		else 
		{
			inter_y += delta_y;
			map_y += step_y;
			side = 1;
		}
		if (main->map[map_x][map_y] == 1)
			//we hit a wall
	}

	//calculate perpendicular distance from camera plane to wall
	if (side = 0)
		wall_dist = inter_x - delta_x;
	else
		wall_dist = inter_y - delta_y

	//once we figure out distance from camera plane to wall, we can calculate wall height
	//wall height = inverse of camera plane * height of screen

}
