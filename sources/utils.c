/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:11:15 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/21 09:02:52 by hbui-vu          ###   ########.fr       */
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

/*bc there are inconsistencies with floats, 
this will get the approx value of float*/
//returns 1 if the numbers are equal
int	ch_num(double num, double comp)
{
	double	tolerance;

	tolerance = 0.000001;
	if (fabs(num - comp) <= tolerance)
		return (1);
	return (0);
}
