/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:46:52 by zsyyida           #+#    #+#             */
/*   Updated: 2023/07/27 10:50:00 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_queue
{
	char			content;
	struct s_queue	*next;
	struct s_queue	*prev;
}	t_queue;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	// int				*row_array;
	int				player;
	int				player_update;
	int				width;
	int				height;
	char			*str;
	char			*str_map;
	char			*n_path;
	char			*s_path;
	char			*w_path;
	char			*e_path;
	char			*f_color;
	char			*c_color;
	// struct s_map	*next;
	// struct s_map	*prev;
}	t_map;
// typedef struct s_map
// {
// 	int	*row_array;
// 	struct s_map *next;
// 	struct s_map *prev;
// }	t_map;

/* test*/
void	print_map(t_map **map, int len);
void	ft_valid_path_visit(t_queue *ptr, t_map *map, int position);
void	ft_valid_path_helper(t_queue *ptr, t_map *map);
void	ft_valid_path(t_map map);
t_queue	*ft_lstnew_dl(int content);
t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new);
void	*ft_dequeue(t_queue *enqueue);
void	error_check(int argc, char **argv);

#endif
