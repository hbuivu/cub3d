/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:27:01 by zsyyida           #+#    #+#             */
/*   Updated: 2023/07/27 14:57:27 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// int	ft_strstr(char *h, char *n)
// {
// 	size_t	n_len;

// 	if (*n == '\0')
// 		return (1);
// 	n_len = ft_strlen(n) + 1;
// 	while (*h != '\0' && n_len > 0)
// 	{
// 		if (ft_strncmp(h, n, n_len) == 0 && *h == *n)
// 			return (0);
// 		h++;
// 		n_len--;
// 	}
// 	return (1);
// }

// int	ft_is_cub(char **argv)
// {
// 	int	len;

// 	len = ft_strlen(argv[1]);
// 	if (len < 5)
// 		return (1);
// 	if (ft_strstr(argv[1], ".cub") == 0)
// 		return (1);
// 	return (0);
// }

void	error_check(int argc, char **argv)
{
	if (argc != 2)
	{
		perror("Error\n wrong number of arguments");
		exit (0);
	}
	// if (ft_is_cub(argv) == 1)
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		perror("Error\n require .cub argument");
		exit(0);
	}
}

void	return_error(t_omap *omap)
{
	t_omap *cur;

	write(2, "Error\n", 6);
	if (map)
	{
		cur = map;
		map = map->next;
		free(cur->row);
		free(cur);
	}
	//free main
	exit(1);
}