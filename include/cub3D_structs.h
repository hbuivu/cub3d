/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:51:08 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/26 18:29:54 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# include "cub3d_rev.h"

enum	e_error
{
	IDENT_ERR,
	NBR_IDENT_ERR,
	XPM_ERR,
	GNL_ERR,
	MALLOC_ERR,
	MAP_ERR,
	MLX_ERR,
	OPEN_ERR,
	PLAYER_ERR,
	WALL_ERR,
	IMG_ERR,
	COMMA_ERR,
	INT_ERR,
	COMMA_PLACE_ERR,
	INVALID_COLOR,
	NONE
};

enum	e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	COL,
	ROW
};

typedef struct s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}	t_queue;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlx;

typedef struct s_pix
{
	int		x;
	int		y;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_pix;

typedef struct s_point
{
	double	scale; //scale against 64 pixels
	double	orig_x; //column slice of wall
	double	orig_y; //how the point would translate on original image y axis
	double	y_dist; //the distance of orig_y from y1
	t_pix	p1; //value of color at (x1, y1)
	t_pix	p2; //value of color at (x2, y2)
}	t_point;

typedef struct s_omap
{
	char			*row;
	struct s_omap	*next;
}	t_omap;

// struct s_sprite
// {
//   double x;
//   double y;
//   int texture;
// }	t_sprite;

//BONUS
// typedef struct s_wall
// {
// 	int				ray;
// 	double			dist;
// 	double			cor_dist;
// 	double			wall_height;
// 	double			wall_slice;
// 	t_img			wall_face;
// 	int				start;
// 	int				stop;
// 	struct s_wall	*next;
// 	struct s_wall	*prev;
// } 	t_wall;

typedef struct	s_calc
{
	double	rad_90;
	double	rad_270;
	double	rad_360;
	double	upg; //units per grid
	double	fov; //field of view in rad
	double	pln_height; //plane height (repeat of main win_height)
	double	pln_width; //plane width (repeate of main win_width)
	double	pln_dist; //plane distance from player
	double	ray_incr; //angle at which ray increments from right to left
	
	/* changing calculations, needed for raycasting and movement */
	double	px; //player spawn x(col) position in unit coordinates
	double	py; //player spawn y(row) position in unit coordinates
	double	pdir; //player direction in rad
	double	angle; //angle used for calculations in degrees
	int		stepx; //direction in which x is going for angle (-1 or 1)
	int		stepy; //direction in which y is going for angle (-1 or 1)
	double	tan_angle; //tangent of angle for calculations;
	
	/* raycasting variables initiated to 0 at start. prob does not need to be reset */
	double	col_int; //point where ray intersects a column line
	double	col_inty; //the y coordinate where ray intersects column line
	double	row_int; //point where ray intersects a row line
	double	row_intx; //the x coordinate where ray intersects a row line
	double	deltax; //movement in x direction every time y moves by 1 grid
	double	deltay; //movement in y direction every time x moves by 1 grid
	double	dist_col; //distance squared of original point to first column intersect with wall
	double	dist_row; //distance squared of original point to first row intersect with wall
	double	cor_dist; //corrected distance from point to closest
	double	wall_height; //projected wall height
	t_img	wall_face; //NSEW
	int		wall_slice;

		/* used for walking */
	int		pdir_stepx; //direction in which x is going for pdir (-1 or 1)
	int		pdir_stepy; //direction in which y is going for pdir (-1 or 1)
	double	tan_pdir; //tangent of pdir for walking calculations
	double	x_walk; //how much player moves in x direction when walking
	double	y_walk; //how much player moves in y direction when walking
	double	x_run; //how much player moves in x direction when running
	double	y_run; //how much player moves in y direction when running
	double	walk_dist; //how far player moves each time they walk;
	double	run_dist; //how far player moves each time they run;

	// //BONUS
	// int		ray;
	// double	castback_px;
	// double	castback_py;
	// t_wall	*wall_list;
	// t_wall	*wall_list_cur;
}	t_calc;

typedef struct s_main
{
	t_omap			*omap; //original map (linked list)
	t_mlx			mlx;
	t_calc			*calc;
	t_img			img;
	/* map info */
	int				*player_pos; //(column, row)
	char			player_dir;
	int				map_width;
	int				map_height;
	char			*n_path;
	char			*s_path;
	char			*w_path;
	char			*e_path;
	int				*f_color;
	int				*c_color;
	char			**map; //final map, access via map[row][column]

	/* zahra */
	t_img			img_minimap;
	t_img			img_no_wall;
	t_img			img_so_wall;
	t_img			img_we_wall;
	t_img			img_ea_wall;
	t_img			img_spr1;
	t_img			img_spr2;
	t_img			img_door1;
	t_img			img_door2;
	int				*player_update;
	char			**map_cpy;
	int				mouse_x;
}	t_main;

#endif