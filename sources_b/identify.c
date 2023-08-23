/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:13:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/22 12:59:23 by zsyyida          ###   ########.fr       */
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
	int		j;

	curr = omap;
	i = 0;
	j = 0;
	while (curr)
	{
		printf("j: %i\n", j);
		// print_omap(main->omap);
		while (curr->row[i] == ' ')
			i++;
		if (curr->row[i] == 'F')
			floor_colour(main, &curr->row[i]);
		else if (curr->row[i] == 'C')
			ceiling_colour(main, &curr->row[i]);
		else if (curr->row[i] == 'N')
			n_path_identity(main, &curr->row[i], "NO");
		else if (curr->row[i] == 'S')
			s_path_identity(main, &curr->row[i], "SO");
		else if (curr->row[i] == 'E')
			e_path_identity(main, &curr->row[i], "EA");
		else if (curr->row[i] == 'W')
			w_path_identity(main, &curr->row[i], "WE");
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
		j++;
	}
	return (NULL);
}

