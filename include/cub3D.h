/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:46:52 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/02 14:36:00 by hbui-vu          ###   ########.fr       */
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

enum	error
{
	GNL_ERR,
	MALLOC_ERR,
	MAP_ERR,
	MLX_ERR,
	OPEN_ERR,
	NONE
};

typedef struct s_queue
{
	char			content;
	struct s_queue	*next;
	struct s_queue	*prev;
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
	double	ray_incr; //angle at which ray increments from right to left
	double	pl_dir; //player direction in rad
	double	angle; //angle used for calculations
	double	pl_x; //player spawn x(col) position in unit coordinates
	double	pl_y; //player spawn y(row) position in unit coordinates
	
	/* initiated to 0 at start */
	int		stepx; //direction in which x is going (-1 or 1)
	int		stepy; //direction in which y is going (-1 or 1)
	double	col_pt; //point where ray intersects a column line
	double	col_pty; //the y coordinate where ray intersects column line
	double	row_pt; //point where ray intersects a row line
	double	row_ptx; //the x coordinate where ray intersects a row line
	int		ch_col; //map column coordinate to check
	int		ch_row; //map row coordinate to check
}	t_calc;

typedef struct s_main
{
	int				win_width;
	int				win_height;
	int				*player_pos; //(column, row)
	char			player_dir;
	int				map_width;
	int				map_height;
	char			**map; //final map
	char			*n_path;
	char			*s_path;
	char			*w_path;
	char			*e_path;
	int				*f_color;
	int				*c_color;
	t_omap			*omap; //original map (linked list)
	t_mlx			mlx;
	t_img			img;
	t_calc			calc;

	/* zahra */
	int				player_update;
}	t_main;

/* utils.c */
void	*cub_calloc(size_t count, size_t size, t_main *main);
void	*cub_malloc(size_t count, size_t size, t_main *main);
/* error.c */
void	error_check(int argc, char **argv);
void	return_error(t_main *main, int err_msg);

/* download.c */
void	download_map(int fd, t_main *main);

/* parse_map.c */
void	parse_map(t_omap *omap_start, t_main *main);

/* test*/
void	print_omap(t_omap *map);
void	print_main_map(t_main *main);

/* parse.c */
char	*identify(t_omap *omap_start, t_main *main);

void	ft_valid_path_visit(t_queue *ptr, t_main *map, int position);
void	ft_valid_path_helper(t_queue *ptr, t_main *map);
void	ft_valid_path(t_main map);
t_queue	*ft_lstnew_dl(int *content);
t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new);
void	*ft_dequeue(t_queue *enqueue);
void	change_space(t_main *map);

#endif
