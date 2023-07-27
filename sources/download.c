#include "../include/cub3D.h"
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

//download omap for parsing
void	download_map(int fd, t_main *main)
{
	char	*str;
	t_omap	*node;
	t_omap	*cur;

	str = get_next_line(fd);
	if (!str)
		return_error(main);
	node = NULL;
	cur = NULL;
	while (str)
	{
		node = ft_calloc(1, sizeof(t_omap));
		if (!node)
		{
			free(str);
			close(fd);
			return_error(main);
		}
		node->row = cub_strdup(str, main);
		if (main->omap == NULL)
			main->omap = node;
		else
			cur->next = node;
		cur = node;
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
}

//need a prev for omap;
void	clean_omap(t_main *main)
{
	t_omap	*cur;

	cur = main->omap;
	while (cur->next)
		cur = cur->next;
	//go to end of omap
	//look for a character in line. if only spaces or \n delete node
	//go to next previous
}
