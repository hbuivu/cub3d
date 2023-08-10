#include "../include/cub3D.h"

void	*cub_calloc(size_t count, size_t size, t_main *main)
{
	void	*buf;

	buf = ft_calloc(count, size);
	if (!buf)
		return_error(main, MALLOC_ERR);
	return (buf);
}

void	*cub_malloc(size_t count, size_t size, t_main *main)
{
	void	*buf;

	buf = malloc(count * size);
	if (!buf)
		return_error(main, MALLOC_ERR);
	return (buf);
}

//special strdup for download_map - does not copy \n if one exists
char	*cub_strdup(const char *s1, t_main *main)
{
	char	*ret_str;
	size_t	i;

	i = 0;
	ret_str = cub_calloc(ft_strlen(s1) + 1, sizeof(char), main);
	while (s1[i] != '\n' && s1[i] != '\0')
	{
		ret_str[i] = s1[i];
		i++;
	}
	return (ret_str);
}

/*
 Destroy a window instance.
	int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
 @param	void *mlx_ptr	the mlx instance;
 @param	void *mlx_win	the window instance;
 @return	int				has no return value (bc).
*/
int	ft_close(t_main *main)
{
	mlx_destroy_window(main->mlx.mlx_ptr, main->mlx.mlx_win);
	// free(main->map);
	exit(0);
}
