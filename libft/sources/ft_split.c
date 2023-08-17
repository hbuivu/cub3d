/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:20:56 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/17 20:57:23 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	num_strs(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			count++;
		i++;
	}
	return (count + 1);
}

static char	*cpystr(char const *s, char c)
{
	char	*buffer;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	buffer = malloc (sizeof(char) * i + 1);
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s, i + 1);
	return (buffer);
}

char	**ft_split(char const *s, char c)
{
	char	**buffer;
	int		i;
	int		strs;

	if (!s)
		return (NULL);
	printf("s %s\n", s);
	strs = num_strs(s, c);
	buffer = (char **)malloc(sizeof(char *) * strs);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < strs - 1)
	{
		printf("i , (strs - 1) %d  %d\n", i , strs - 1);
		while (*s == c)
			s++;
		buffer[i] = cpystr(s, c);
	printf("buffer[i] in split %s\n", buffer[i]);
		if (!buffer[i])
			return (NULL);
		i++;
		s = ft_strchr(s, c);
	}
	buffer[i] = NULL;
	printf("buffer %s\n", buffer[0]);
	return (buffer);
}
