
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

// void	print_calc(t_main *main)
// {
// 	printf("upg: %lf\n", main->calc->upg);
// 	printf("fov: %lf\n", main->calc->fov);
// 	printf("pln_height: %lf\n", main->calc->pln_height);
// 	printf("pln_width: %lf\n", main->calc->pln_width);
// 	printf("pln_dist: %lf\n", main->calc->pln_dist);
// printf("px: %lf\n", main->calc->px);
// printf("py: %lf\n", main->calc->py);
// 	printf("pdir: %lf\n", main->calc->pdir);
// 	printf("ray_incr: %lf\n", main->calc->ray_incr);
// 	printf("angle: %lf\n", main->calc->angle);
// 	printf("stepx: %i\n", main->calc->stepx);
// 	printf("stepy: %i\n", main->calc->stepy);
// 	printf("col_int: %lf\n", main->calc->col_int);
// 	printf("col_inty: %lf\n", main->calc->col_inty);
// 	printf("row_int: %lf\n", main->calc->row_int);
// 	printf("row_intx: %lf\n", main->calc->row_intx);
// 	printf("int: col_int: %i\n", (int)(main->calc->col_int / main->calc->upg));
// 	printf("int: col_inty: %i\n", (int)(main->calc->col_inty / main->calc->upg));
// 	printf("int: row_int: %i\n", (int)(main->calc->row_int / main->calc->upg));
// 	printf("int: row_intx: %i\n", (int)(main->calc->row_intx / main->calc->upg));
// 	printf("deltax: %lf\n", main->calc->deltax);
// 	printf("deltay: %lf\n", main->calc->deltay);
// 	printf("dist_col: %lf", main->calc->dist_col);
// 	printf("dist_row: %lf", main->calc->dist_row);
// 	printf("cor_dist: %lf", main->calc->cor_dist);
// }

// void	print_main(t_main *main)
// {
// 	printf("********* ORIGINAL CUB FILE *********\n");
// 	print_omap(main->omap);
// 	printf("********* MAIN STRUCT *********\n");
// 	printf("win_width: %i\n", WIN_WIDTH);
// 	printf("win_height: %i\n", WIN_HEIGHT);
// 	printf("player position (row, col): %i, %i\n", main->player_pos[0], main->player_pos[1]);
// 	printf("player dir: %c\n", main->player_dir);
// 	printf("map_width: %i\n", main->map_width);
// 	printf("map_height: %i\n", main->map_height);
// 	printf("n_path: %s\n", main->n_path);
// 	printf("s_path: %s\n", main->s_path);
// 	printf("w_path: %s\n", main->w_path);
// 	printf("e_path: %s\n", main->e_path);
// 	// printf("f_color: %i, %i, %i\n", main->f_color[0], main->f_color[1], main->f_color[2]);
// 	// printf("c_color: %i, %i, %i\n", main->c_color[0], main->c_color[1], main->c_color[2]);
// 	print_main_map(main);
// 	printf("********* CALCULATIONS *********\n");
// 	print_calc(main);
// }