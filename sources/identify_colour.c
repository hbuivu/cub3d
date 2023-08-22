/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_colour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:45:40 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/21 17:02:59 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*remove_spaces(char *s, t_main *main)
{
	char	*number;
	int		i;
	int		j;

	i = 0;
	while (s[i] == ' ')
		i++;
	number = cub_calloc(((int)ft_strlen(s) - i + 1), sizeof(char), main);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ')
		{
			number[j] = s[i];
			i++;
			j++;
		}
		else
			i++;
	}
	number[j] = '\0';
	return (number);
}

char	*check_comma(char *s, t_main *main)
{
	int		i;
	int		comma;

	s = remove_spaces(s, main);
	comma = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
		{
			comma++;
			if (!(s[i - 1] >= '0' && s[i - 1] <= '9')
				|| (!(s[i + 1] >= '0' && s[i + 1] <= '9')))
				return_error(main, COMMA_PLACE_ERR);
		}
		else if (!(s[i] >= '0' && s[i] <= '9'))
			return_error(main, INT_ERR);
		i++;
	}
	if (comma != 2)
		return_error(main, COMMA_ERR);
	return (s);
}

int	*to_int(char *s, t_main *main)
{
	char	**split;
	int		*color;
	int		i;

	color = cub_calloc(4, sizeof(int), main);
	s = check_comma(s, main);
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
	if (!color[3])
		color[3] = 255;
	return (color);
}

void	floor_colour(t_main *main, char *s)
{
	if (main->f_color != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(s, "F", 1) != 0)
		return_error(main, IDENT_ERR);
	s = s + 1;
	while (*s == ' ')
		s = s + 1;
	main->f_color = to_int(s, main);
}

void	ceiling_colour(t_main *main, char *s)
{
	if (main->c_color != NULL)
		return_error(main, NBR_IDENT_ERR);
	if (ft_strncmp(s, "C ", 2) != 0)
		return_error(main, IDENT_ERR);
	s = s + 1;
	while (*s == ' ')
		s = s + 1;
	main->c_color = to_int(s, main);
}
