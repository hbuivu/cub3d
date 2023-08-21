/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:46:52 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/21 16:59:34 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
// # include <X11/keysym.h>

// from KEYCODES minilibx for ASDW and keycode for arrow keys
# define LEFT_KEY				123
# define RIGHT_KEY				124
# define A_KEY					0
# define S_KEY					1
# define D_KEY					2
# define W_KEY					13
# define ESC 					53
# define TW						64	// width of the texture
# define TH						64  //height of texture
# define SIZE					1  //size of the texture
// # define GL_SILENCE_DEPRECATION
# define WIN_WIDTH				1920
# define WIN_HEIGHT				1024

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
	NONE
};

enum	e_compass
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
	char	**buff;
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
	double	orig_y; //how the point would transalte on original image y axis
	double	y_dist; //the distance of orig_y from y1
	t_pix	p1; //value of color at (x1, y1)
	t_pix	p2; //value of color at (x2, y2)
}	t_point;

typedef struct s_omap
{
	char			*row;
	struct s_omap	*next;
}	t_omap;

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
	double	px; //player spawn x(col) position in unit coordinates
	double	py; //player spawn y(row) position in unit coordinates
	double	pdir; //player direction in rad
	double	ray_incr; //angle at which ray increments from right to left
	/* recalculated each ray */
	double	angle; //angle used for calculations in degrees
	int		stepx; //direction in which x is going (-1 or 1)
	int		stepy; //direction in which y is going (-1 or 1)
	double	tan_angle; //tangent of angle for calculations;
	/* initiated to 0 at start */
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
}	t_calc;

typedef struct s_main
{
	t_omap			*omap; //original map (linked list)
	t_mlx			mlx;
	t_calc			*calc;
	t_img			img;
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
}	t_main;

/* error.c */
void	error_check(int argc, char **argv);
void	return_error(t_main *main, int err_msg);

/* utils.c */
void	*cub_calloc(size_t count, size_t size, t_main *main);
char	*cub_strdup(const char *s1, t_main *main);
int		ch_num(double angle, double comp);

/* parse_map.c */
void	download_map(int fd, t_main *main);
void	check_map(t_omap *omap_start, t_main *main);
void	get_map(t_omap *ptr_map, t_main *main);

/* mlx_hooks.c */
int		ft_close(t_main *main);
int		key_press(int key_code, t_main *main);

/* mlx_imgs.c */
void	mlx(t_main *main);
void	get_textures(t_main *main);
void	get_data_addr(t_main *main);

/* calc.c */
void	calc_step(t_main *main);
void	init_calc(t_main *main);
void	recalc(t_main *main);

/* coord_check.c */
int	check_coord(int jump, t_main *main);

/* draw.c */
void	draw_wall(int x, t_main *main);
void	draw_floor_ceiling(t_main *main);

/* draw_utils.c */
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	ft_pixel_put(t_img *img, int x, int y, int color);

/* raycasting.c */
void	raycast(t_main *main);

/* test*/
void	print_omap(t_omap *map);
void	print_main_map(t_main *main);
void	print_calc(t_main *main);
void	print_main(t_main *main);


/* identify.c */
t_omap	*identify(t_omap *omap, t_main *main);

void	floor_colour(t_main *main, char *ptr);
void	ceiling_colour(t_main *main, char *ptr);
int		*to_int(char *s, t_main *main);

void	n_path_identity(t_main *main, char *s, char *id);
void	s_path_identity(t_main *main, char *s, char *id);
void	w_path_identity(t_main *main, char *s, char *id);
void	e_path_identity(t_main *main, char *s, char *id);

void	visit(t_queue *ptr, t_main *main, int x, int y);
void	check_walled_helper(t_queue *ptr, t_main *main);
void	check_walled(t_main *main);
t_queue	*ft_lstnew_dl(int x, int y);
t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new);
void	*ft_dequeue(t_queue *enqueue);
void	del(void *lst);

void	draw_minimap(t_main *main);

#endif
