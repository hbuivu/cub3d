/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:27:03 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/17 21:27:04 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	*cub_calloc(size_t count, size_t size, t_main *main)
{
	void	*buf;

	buf = ft_calloc(count, size);
	if (!buf)
		return_error(main, MALLOC_ERR);
	return (buf);
}

void	*cub_malloc(size_t count, size_t size, t_main *main)
{
	void	*buf;

	buf = malloc(count * size);
	if (!buf)
		return_error(main, MALLOC_ERR);
	return (buf);
}

//special strdup for download_map - does not copy \n if one exists
char	*cub_strdup(const char *s1, t_main *main)
{
	char	*ret_str;
	size_t	i;

	i = 0;
	ret_str = cub_calloc(ft_strlen(s1) + 1, sizeof(char), main);
	while (s1[i] != '\n' && s1[i] != '\0')
	{
		ret_str[i] = s1[i];
		i++;
	}
	return (ret_str);
}
