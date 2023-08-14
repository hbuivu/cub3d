/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_colour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:45:40 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/14 21:04:05 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	check_comma(char *s, t_main *main)
{
	int		i;
	int		comma;

	comma = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			comma++;
		else if (!(s[i] >= '0' && s[i] <= '9'))
			return_error(main, INT_ERR);
		i++;
	}
	if (comma != 2)
		return_error(main, COMMA_ERR);
}

int	*to_int(char *s, t_main *main)
{
	char	**split;
	int		*color;
	int		i;

	check_comma(s, main);
	color = ft_calloc(4, sizeof(int));
	split = ft_split(s, ',');
	i = 0;
	while (split[i])
	{
		color[i] = ft_atoi(split[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			perror("Not a valid color");
			exit(1);
		}
		i++;
	}
	return (color);
}

void	floor_colour(t_main *main, int i, char *s)
{
	if (main->f_color != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(&s[i], "F", 1) != 0)
		return_error(main, IDENT_ERR);
	i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	main->f_color = to_int(&s[i], main);
}

void	ceiling_colour(t_main *main, int i, char *s)
{
	if (main->c_color != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(&s[i], "C ", 2) != 0)
		return_error(main, IDENT_ERR);
	i++;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	main->c_color = to_int(&s[i], main);
}
