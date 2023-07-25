#ifndef CUBED_H
# define CUBED_H

# include "./mlx/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	int	*row_array;
	struct s_map *next;
	struct s_map *prev;
}	t_map;

/* test*/
void	print_map(t_map **map, int len);

#endif