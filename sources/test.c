#include "../include/cub3D.h"

void	print_omap(t_omap *map)
{
	t_omap *row;

	if (!map)
		return ;
	row = map;
	while (row)
	{
		printf("%s\n", row->row);
		row = row->next;
	}
}

void	print_main_map(t_main *main)
{
	int i;

	i = 0;
	while (main->map[i])
	{
		printf("%s\n", main->map[i]);
		i++;
	}
}

void	print_calc(t_main *main)
{
	printf("upg: %lf\n", main->calc->upg);
	printf("fov: %lf\n", main->calc->fov);
	printf("r_fov: %lf\n", main->calc->rfov);
	printf("pln_height: %lf\n", main->calc->pln_height);
	printf("pln_width: %lf\n", main->calc->pln_width);
	printf("pln_dist: %lf\n", main->calc->pln_dist);
	printf("px: %lf\n", main->calc->px);
	printf("py: %lf\n", main->calc->py);
	printf("pdir: %i\n", main->calc->pdir);
	printf("ray_incr: %lf\n", main->calc->ray_incr);
	printf("angle: %lf\n", main->calc->angle);
	printf("r_angle: %lf\n", main->calc->r_angle);
	printf("stepx: %i\n", main->calc->stepx);
	printf("stepy: %i\n", main->calc->stepy);
	printf("col_int: %lf\n", main->calc->col_int);
	printf("col_int_y: %lf\n", main->calc->col_int_y);
	printf("row_int: %lf\n", main->calc->row_int);
	printf("row_int_x: %lf\n", main->calc->row_int_x);
	printf("int: col_int: %i\n", (int)main->calc->col_int);
	printf("int: col_int_y: %i\n", (int)main->calc->col_int_y);
	printf("int: row_int: %i\n", (int)main->calc->row_int);
	printf("int: row_int_x: %i\n", (int)main->calc->row_int_x);
	printf("deltax: %lf\n", main->calc->deltax);
	printf("deltay: %lf\n", main->calc->deltay);
}