/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:51:08 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/30 20:46:55 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	/* for sprites */
	double	x_dist;
	t_pix	p3;
	t_pix	p4;
	double	r1;
	double	r2;
	double	r;
	double	g1;
	double	g2;
	double	g;
	double	b1;
	double	b2;
	double	b;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
}	t_point;

typedef struct s_omap
{
	char			*row;
	struct s_omap	*next;
}	t_omap;

typedef	struct s_sprite
{
	double	sp_gridx; //large grid coordinate x
	double	sp_gridy; //large grid coordinate y
	double	sp_dist; //distance sprite is from player
	double	spx; //small grid coordinate x
	double	spy; //small grid coordinate y
	double	vx; //x vector between player and sprite
	double	vy; //y vector between player and sprite
	double	vangle; //angle between x axis and vec
	double	rel_vangle; //relative angle between vector and leftmost FOV angle
	double	plnx; //sprite x coordinate on projection plane
	double	plny; //sprite y coordinate on projection plane
	double	sp_height;
	double	sp_width; //always equaly to sp height
	int		start_col; //init to -1 at the beginning, tells you which column to begin rendering sprite slice
	int		end_col; //init to -1 at beginning, tells you which column to end rendering of sprite slice
	int		render;
	int		texture; 
}	t_sprite;

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
	double	fov; //field of view in rad
	double	midpt; //half of plane height, indicates midpt of walls and sprites
	double	pln_dist; //plane distance from player
	double	height_ratio; //constant ratio (texture_height * plane_distance) - used to find height of object in plane
	double	ray_incr; //angle at which ray increments from right to left

	/* changing calculations, needed for raycasting and movement */
	double	px; //player spawn x(col) position in unit coordinates
	double	py; //player spawn y(row) position in unit coordinates
	double	pdir; //player direction in rad
	double	angle; //angle used for calculations in degrees
	double	rel_angle; //angle of ray being cast relative to pdir
	int		stepx; //direction in which x is going for angle (-1 or 1)
	int		stepy; //direction in which y is going for angle (-1 or 1)
	double	tan_angle; //tangent of angle for calculations;
	/* moving */
	double	move_angle; //angle at which the player will be moving
	double	x_walk; //how much player moves in x direction when walking
	double	y_walk; //how much player moves in y direction when walking

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

	/* BONUS: sprites */
	double	col_to_fov_ratio; //constant, win_width / FOV, how many columns for 1 degree of fov
	int		x; //ray counter

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
	t_img		*texture;
	t_sprite	*sprite;
	int			sprite_num;
	double		*z_buffer;
	double		*pl_to_sp_dist;
}	t_main;

	// int			texture;
	// double		transform_x;
	// double		transform_y;
	// int			screen_x;
	// int			height;
	// int			draw_start_y;
	// int			draw_end_y;
	// int			width;
	// int			draw_start_x;
	// int			draw_end_x;

#endif