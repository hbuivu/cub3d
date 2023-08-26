/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:13:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 19:01:55 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


/*
1. Make sure F and C are there
2. Make sure NO, SO, WE, EA is there
3. After that, is the map
*/

int	check_main(t_main *main)
{
	if (main->n_path == NULL)
		return (1);
	if (main->s_path == NULL)
		return (1);
	if (main->w_path == NULL)
		return (1);
	if (main->e_path == NULL)
		return (1);
	if (main->f_color == NULL)
		return (1);
	if (main->c_color == NULL)
		return (1);
	if (main->n_path == NULL)
		return (1);
	return (0);
}

int	check_identity(t_main *main, char *s, int i)
{
	printf("hi");
	if (*s == 'F')
		floor_colour(main, s);
	else if (s[i] == 'C')
		ceiling_colour(main, s);
	else if (s[i] == 'N')
		n_path_identity(main, s, "NO");
	else if (s[i] == 'S')
		s_path_identity(main, s, "SO");
	else if (s[i] == 'E')
		e_path_identity(main, s, "EA");
	else if (s[i] == 'W')
		w_path_identity(main, s, "WE");
	else if (ft_strchr(s, '1') != NULL
		|| ft_strchr(s, '0') != NULL
		|| ft_strchr(s, ' ') != NULL)
	{
		if (check_main(main) == 1)
		{
			return (1);
		}
	}
	i = 0;
	while (main->f_color[i])
	{
		printf("%d\n%d\n", main->f_color[i], main->c_color[i]);
		i++;
	}
	printf("%s\n%s\n%s\n%s\n", main->n_path, main->s_path, main->e_path, main->w_path);
	return (0);
}

// printf("%s\n%s\n%s\n%s\n", main->n_path, main->s_path, main->e_path, main->w_path);
// int i = 0;
// while (main->f_color[i])
// {
// 	printf("%d\n%d\n", main->f_color[i], main->c_color[i]);
// 	i++;
// }
// add free and exit
t_omap	*identify(t_omap *omap, t_main *main)
{
	t_omap	*curr;
	t_omap	*ptr_map;
	int		i;

	curr = omap;
	i = 0;
	while (curr)
	{
		while (curr->row[i] == ' ')
			i++;
		if (curr->row[i] == 'F' || curr->row[i] == 'C' || curr->row[i] == 'N' || curr->row[i] == 'S' || curr->row[i] == 'E' || curr->row[i] == 'W')
			check_identity(main, curr->row, i);
		// if (curr->row[i] == 'F')
		// 	floor_colour(main, &curr->row[i]);
		// else if ()
		// 	ceiling_colour(main, &curr->row[i]);
		// else if (curr->row[i] == 'N')
		// 	n_path_identity(main, &curr->row[i], "NO");
		// else if (curr->row[i] == 'S')
		// 	s_path_identity(main, &curr->row[i], "SO");
		// else if (curr->row[i] == 'E')
		// 	e_path_identity(main, &curr->row[i], "EA");
		// else if (curr->row[i] == 'W')
		// 	w_path_identity(main, &curr->row[i], "WE");
		else if (ft_strchr(curr->row, '1') != NULL
			|| ft_strchr(curr->row, '0') != NULL
			|| ft_strchr(curr->row, ' ') != NULL)
		{
			if (check_main(main) == 1)
			{
				return (NULL);
			}
			ptr_map = curr;
			return (ptr_map);
		}
		curr = curr->next;
	}

	return (NULL);
}

