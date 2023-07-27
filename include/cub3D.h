/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:46:52 by zsyyida           #+#    #+#             */
/*   Updated: 2023/07/27 17:54:18 by hbui-vu          ###   ########.fr       */
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

typedef struct s_queue
{
	char			content;
	struct s_queue	*next;
	struct s_queue	*prev;
}	t_queue;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_omap
{
	char			*row;
	struct s_omap	*next;
}	t_omap;

typedef struct s_main
{
	int				*player_pos; //(column, row)
	int				player_update;
	char			player_dir;
	int				map_width;
	int				map_height;
	char			**map;
	char			*n_path;
	char			*s_path;
	char			*w_path;
	char			*e_path;
	int				*f_color;
	int				*c_color;
	t_omap			*omap; //original map

	/* delete later */
	char			*str_map;
	int				player;
	int				width;
	int				height;
	char			*str;
}	t_main;

/* utils.c */
void	*cub_calloc(size_t count, size_t size, t_main *main);
void	*cub_malloc(size_t count, size_t size, t_main *main);
/* error.c */
void	error_check(int argc, char **argv);
void	return_error(t_main *main);

/* download.c */
void	download_map(int fd, t_main *main);

/* parse_map.c */
void	parse_map(t_omap *omap_start, t_main *main);

/* test*/
void	print_omap(t_omap *map);

/* parse.c */
void	identify(char *str, t_main *map, char **argv, int fd);

void	ft_valid_path_visit(t_queue *ptr, t_main *map, int position);
void	ft_valid_path_helper(t_queue *ptr, t_main *map);
void	ft_valid_path(t_main map);
t_queue	*ft_lstnew_dl(int content);
t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new);
void	*ft_dequeue(t_queue *enqueue);

#endif
