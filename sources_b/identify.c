/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:13:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/28 17:08:35 by zsyyida          ###   ########.fr       */
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

void	check_identity(t_main *main, char *row)
{
	int	i;
	
	i = 0;
	while (row[i] == ' ')
		i++;
	if (row[i] == 'F')
		floor_colour(main, &row[i]);
	else if (row[i] == 'C')
		ceiling_colour(main, &row[i]);
	else if (row[i] == 'N')
		n_path_identity(main, &row[i], "NO");
	else if (row[i] == 'S')
		s_path_identity(main, &row[i], "SO");
	else if (row[i] == 'E')
		e_path_identity(main, &row[i], "EA");
	else if (row[i] == 'W')
		w_path_identity(main, &row[i], "WE");
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
	while (curr)
	{
		i = 0;
		while (curr->row[i] == ' ')
			i++;
		if (curr->row[i] == 'F' || curr->row[i] == 'C' || curr->row[i] == 'N' 
			|| curr->row[i] == 'S' || curr->row[i] == 'E' || *curr->row == 'W')
			check_identity(main, curr->row);
		else if (ft_strchr(curr->row, '1') != NULL
		|| ft_strchr(curr->row, '0') != NULL
		|| ft_strchr(curr->row, ' ') != NULL)
		{
			if (check_main(main) == 1)
				return (NULL);
			ptr_map = curr;
			return (ptr_map);
		}
		curr = curr->next;
	}
	return (NULL);
}

