/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:49:12 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/14 21:18:24 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	n_path_identity(t_main *main, int i, char *s, char *id)
{
	if (main->n_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(&s[i] + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	if (ft_strncmp(&s[i], id, 2) != 0)
		return_error(main, IDENT_ERR);
	i = i + 2;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	main->n_path = cub_strdup(&s[i], main);
}

void	s_path_identity(t_main *main, int i, char *s, char *id)
{
	if (main->s_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(&s[i] + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	if (ft_strncmp(&s[i], id, 2) != 0)
		return_error(main, IDENT_ERR);
	i = i + 2;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	main->s_path = cub_strdup(&s[i], main);
}


void	e_path_identity(t_main *main, int i, char *s, char *id)
{
	if (main->e_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(&s[i] + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	if (ft_strncmp(&s[i], id, 2) != 0)
		return_error(main, IDENT_ERR);
	i = i + 2;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	main->e_path = cub_strdup(&s[i], main);
}

void	w_path_identity(t_main *main, int i, char *s, char *id)
{
	if (main->w_path != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(&s[i] + ft_strlen(s) - 4, ".xpm", 4) != 0)
		return_error(main, XPM_ERR);
	if (ft_strncmp(&s[i], id, 2) != 0)
		return_error(main, IDENT_ERR);
	i = i + 2;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	main->w_path = cub_strdup(&s[i], main);
}
