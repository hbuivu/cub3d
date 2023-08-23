#include "../include/cub3D.h"

/* 
second idea
1. move player to new px and py position
2. check px and py to see if it is in a wall
3. if it's in a wall, return player to original position
*/

void	calc_move(int key, t_main *main)
{
	t_calc *c;

	c = main->calc;
	if (key == W_KEY)
	{
		c->x_walk = round(fabs(cos(c->pdir)) * WALK * c->pdir_stepx); //should we round bc the player cannot walk half a pixel
		c->y_walk = round(fabs(sin(c->pdir)) * WALK * c->pdir_stepy);
	}
	else if (key == S_KEY)
	{
		c->x_walk = round(fabs(cos(c->pdir)) * WALK * c->pdir_stepx * -1);
		c->y_walk = round(fabs(sin(c->pdir)) * WALK * c->pdir_stepy * -1);
	}
	else if (key == A_KEY)
	{
		c->x_walk = round(fabs(sin(c->pdir)) * WALK) * -1;
		c->y_walk = round(fabs(cos(c->pdir)) * WALK);
	}
	else if (key == D_KEY)
	{
		c->x_walk = round(fabs(sin(c->pdir)) * WALK);
		c->y_walk = round(fabs(cos(c->pdir)) * WALK) * -1;
	}
}

void	check_collision(int	key, t_main *main)
{
	/* col = new_px / 64, row = new_py / 64 */
	t_calc	*c;
	double	new_px;
	double	new_py;
	// double	mod_x;
	// double	mod_y;

	c = main->calc;
	calc_move(key, main);
	new_px = c->px + c->x_walk;
	new_py = c->py + c->y_walk;
	// mod_x = fmod(new_px, 64.0);
	// mod_y = fmod(new_py, 64.0);
	printf("new_px: %lf new_py: %lf\n", new_px, new_py);
	// printf("row: %i col: %i\n", (int)((new_py) /64), (int)((new_px)/64));
	// printf("map: %c\n", main->map[(int)((new_py) / 64)][(int)((new_px) / 64)]);

	// if (main->map[(int)(new_py / 64)][(int)(new_px/ 64)] != '1')
	if (main->map[(int)(new_py / c->upg)][(int)((new_px + (WALL_BUFF * c->pdir_stepx)) / c->upg)] != '1' &&
		main->map[(int)((new_py + (WALL_BUFF * c->pdir_stepy)) / c->upg)][(int)(new_px / c->upg)] != '1')
	{
		c->px = new_px;
		c->py = new_py;
	}
	//which direction is px and py heading in 
	//check for a wall in that direction
	//
}
