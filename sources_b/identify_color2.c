/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_color2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:49:11 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 15:51:55 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	digit_check(char *s, int i, t_main *main)
{
	if (!(s[i - 1] >= '0' && s[i - 1] <= '9')
		|| (!(s[i + 1] >= '0' && s[i + 1] <= '9')))
	{
		free(s);
		return_error(main, COMMA_PLACE_ERR);
	}
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
