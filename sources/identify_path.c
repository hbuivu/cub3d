/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:49:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/21 14:33:57 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*trim_trailing_spaces(char *s, t_main *main)
{
	char	*temp;
	int		j;
	int		i;

	temp = cub_calloc((int)ft_strlen(s) + 1, sizeof(char), main);
	j = 0;
	i = 0;
	while (s[j] && s[j] == ' ')
		j++;
	while (s[j] && s[j] != ' ')
	{
		temp[i] = s[j];
		j++;
		i++;
	}
	while (s[j])
	{
		if (s[j] != ' ')
			return_error(main, MAP_ERR);
		j++;
	}
	return (temp);
}

void	n_path_identity(t_main *main, char *s, char *id)
{
	if (main->n_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(s, id, 2) != 0)
		return_error(main, IDENT_ERR);
	s = s + 2;
	s = trim_trailing_spaces(s, main);
	if (ft_strncmp(s + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	while (*s == ' ')
		s = s + 1;
	main->n_path = cub_strdup(s, main);
}

void	s_path_identity(t_main *main, char *s, char *id)
{
	if (main->s_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(s, id, 2) != 0)
		return_error(main, IDENT_ERR);
	s = s + 2;
	s = trim_trailing_spaces(s, main);
	if (ft_strncmp(s + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	while (*s == ' ')
		s = s + 1;
	main->s_path = cub_strdup(s, main);
}

void	e_path_identity(t_main *main, char *s, char *id)
{
	if (main->e_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(s, id, 2) != 0)
		return_error(main, IDENT_ERR);
	s = s + 2;
	s = trim_trailing_spaces(s, main);
	if (ft_strncmp(s + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	while (*s == ' ')
		s = s + 1;
	main->e_path = cub_strdup(s, main);
}

void	w_path_identity(t_main *main, char *s, char *id)
{
	if (main->w_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(s, id, 2) != 0)
		return_error(main, IDENT_ERR);
	s = s + 2;
	s = trim_trailing_spaces(s, main);
	if (ft_strncmp(s + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	while (*s == ' ')
		s = s + 1;
	main->w_path = cub_strdup(s, main);
}
