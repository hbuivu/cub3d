#include "../include/cub3D.h"
//download omap for parsing
void	download_map(int fd, t_main *main)
{
	char	*str;
	t_omap	*node;
	t_omap	*cur;

	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		return_error(main, GNL_ERR);
	}
	node = NULL;
	cur = NULL;
	while (str)
	{
		node = ft_calloc(1, sizeof(t_omap));
		if (!node)
		{
			free(str);
			close(fd);
			return_error(main, MALLOC_ERR);
		}
		node->row = cub_strdup(str, main);
		if (main->omap == NULL)
			main->omap = node;
		else
		{
			node->prev = cur;
			cur->next = node;
		}
		cur = node;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
}

//do we need a clean_omap if there are extra spaces after the map ends?
