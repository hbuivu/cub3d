/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   download.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:37:22 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/18 02:20:22 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//download omap for parsing
void	create_node(t_omap *node, char *str, int fd, t_main *main)
{
	node = ft_calloc(1, sizeof(t_omap));
	if (!node)
	{
		free(str);
		close(fd);
		return_error(main, MALLOC_ERR);
	}
	node->row = cub_strdup(str, main);
}

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
	while (str)
	{
		create_node(node, str, fd, main);
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
