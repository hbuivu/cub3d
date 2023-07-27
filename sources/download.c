#include "../include/cub3D.h"

//download omap for parsing
void	download_map(int fd, t_omap **omap, t_main *main)
{
	char	*str;
	t_omap	*node;
	t_omap	*cur;

	(void)main;
	str = get_next_line(fd);
	if (!str)
		exit(1);
	node = NULL;
	cur = NULL;
	while (str)
	{
		node = ft_calloc(sizeof(t_omap), 1);
		if (!node)
			exit(1);
		node->row = ft_strdup(str);
		if (*omap == NULL)
			*omap = node;
		else
			cur->next = node;
		cur = node;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
}
