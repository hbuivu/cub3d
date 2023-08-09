/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walled_check_utilities.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:00:11 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/09 11:32:34 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	del(void *lst)
{
	free (lst);
}

t_queue	*ft_lstnew_dl(int x, int y)
{
	t_queue	*new;

	new = ft_calloc(1, sizeof(t_queue));
	if (new == NULL)
		return (0);
	new -> x = x;
	new ->y = y;
	new -> next = NULL;
	return (new);
}

t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new)
{
	t_queue	*ptr;

	if (new == NULL)
		return (*queue);
	ptr = *queue;
	if (!ptr)
		ptr = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (*queue);
}

void	*ft_dequeue(t_queue *enqueue)
{
	enqueue->next = NULL;
	del (enqueue);
	return (NULL);
}
