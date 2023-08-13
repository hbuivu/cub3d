/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:46:52 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/13 19:19:45 by hbui-vu          ###   ########.fr       */
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

// from KEYCODES minilibx for ASDW and keycode for arrow keys
# define LEFT_KEY				123
# define RIGHT_KEY				124
# define A_KEY					0
# define S_KEY					1
# define D_KEY					2
# define W_KEY					13
# define ESC 					53
# define TW				64	// width of the texture
# define TH				64  //height of texture
# define SIZE					1  //size of the texture		
// # define GL_SILENCE_DEPRECATION

enum	error
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
	NONE
};

enum	compass
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

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_mlx;

typedef struct s_omap
{
	char			*row;
	struct s_omap	*next;
	struct s_omap	*prev;
}	t_omap;

typedef struct	s_calc
{
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
	int		wall_face; //NSEW
}	t_calc;

typedef struct s_main
{
	t_omap			*omap; //original map (linked list)
	int				win_width;
	int				win_height;
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
	t_mlx			mlx;
	t_calc			*calc;
	double			n_angle;
	double			s_angle;
	double			e_angle;
	double			w_angle;

	t_img			img;
	
	/* zahra */
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

/* utils.c */
void	*cub_calloc(size_t count, size_t size, t_main *main);
void	*cub_malloc(size_t count, size_t size, t_main *main);
char	*cub_strdup(const char *s1, t_main *main);

/* error.c */
void	error_check(int argc, char **argv);
void	return_error(t_main *main, int err_msg);

/* download.c */
void	download_map(int fd, t_main *main);

/* parse_map.c */
void	parse_map(t_omap *omap_start, t_main *main);
void	get_map(t_omap *ptr_map, t_main *main);

/* raycasting.c */
void	raycast(t_main *main);
void	init_calc(t_main *main);
void	calc_step(t_main *main);

/* mlx.c */
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	mlx(t_main *main);
int		ft_close(t_main *main);
int		ft_movement(int key_code, t_main *main);

/* test*/
void	print_omap(t_omap *map);
void	print_main_map(t_main *main);
void	print_calc(t_main *main);
void	print_main(t_main *main);

/* identify.c */
t_omap	*identify(t_omap *omap_start, t_main *main);
void	visit(t_queue *ptr, t_main *main, int x, int y);
void	check_walled_helper(t_queue *ptr, t_main *main);
void	check_walled(t_main *main);
t_queue	*ft_lstnew_dl(int x, int y);
t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new);
void	*ft_dequeue(t_queue *enqueue);
void	del(void *lst);

void	get_textures(t_main *main);
void	get_data_addr(t_main *main);

#endif
