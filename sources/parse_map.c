/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:14:26 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/30 13:50:24 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//download omap for parsing
t_omap	*create_node(char *str, int fd, t_main *main)
{
	t_omap	*node;

	node = ft_calloc(1, sizeof(t_omap));
	if (!node)
	{
		free(str);
		close(fd);
		return_error(main, MALLOC_ERR);
	}
	node->row = cub_strdup(str, main);
	return (node);
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
		node = create_node(str, fd, main);
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

//returns the length of row
//only_spaces checks if line contains only spaces and no other characters
int	check_row(t_omap *cur, t_main *main)
{
	int	i;
	int	only_spaces;

	i = -1;
	only_spaces = 1;
	while (cur->row[++i])
	{
		if (cur->row[i] == '\n')
			return (0);
		if (!ft_strchr(" NSEW01", cur->row[i]))
			return_error(main, MAP_ERR);
		if (ft_strchr("NSEW01", cur->row[i]))
			only_spaces = 0;
		if (ft_strchr("NSEW", cur->row[i]))
		{
			if (main->player_dir != '\0' || main->player_pos != NULL)
				return_error(main, PLAYER_ERR);
			main->player_dir = cur->row[i];
			main->player_pos = (int *)cub_calloc(2, sizeof(int), main);
			main->player_pos[0] = i;
			main->player_pos[1] = main->map_height;
		}
	}
	if (only_spaces)
		return (0);
	return (i);
}

void	check_map(t_omap *omap_start, t_main *main)
{
	t_omap	*cur;
	int		row_len;
	int		empty_line;

	if (omap_start == NULL)
		return_error(main, MAP_ERR);
	cur = omap_start;
	empty_line = 0;
	while (cur)
	{
		row_len = check_row(cur, main);
		if (row_len != 0 && empty_line == 1)
			return_error(main, MAP_ERR);
		if (row_len == 0)
			empty_line = 1;
		main->map_height++;
		if (main->map_width < row_len)
			main->map_width = row_len;
		cur = cur->next;
	}
	if (main->player_dir == '\0')
		return_error(main, MAP_ERR);
}

//converts any spaces to 0
//typecast cub_calloc later
void	get_map(t_omap *ptr_map, t_main *main)
{
	t_omap	*cur;
	int		i;
	int		j;

	i = -1;
	j = -1;
	cur = ptr_map;
	main->map = (char **)cub_calloc(main->map_height + 1, sizeof(char *), main);
	while (++i < main->map_height)
	{
		main->map[i] = cub_calloc(main->map_width + 1, sizeof(char), main);
		while (cur->row[++j])
		{
			main->map[i][j] = cur->row[j];
			if (cur->row[j] == ' ')
				main->map[i][j] = '0';
		}
		while (j < main->map_width)
		{
			main->map[i][j] = '0';
			j++;
		}
		j = -1;
		cur = cur->next;
	}
}
