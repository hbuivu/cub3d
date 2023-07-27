#include "../include/cub3D.h"

void	*cub_calloc(size_t count, size_t size, t_main *main)
{
	void	*buf;

	buf = ft_calloc(count, size);
	if (!buf)
		return_error(main);
	return (buf);
}

void	*cub_malloc(size_t count, size_t size, t_main *main)
{
	void	*buf;

	buf = malloc(count * size);
	if (!buf)
		return_error(main);
	return (buf);
}
