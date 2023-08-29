/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:54:07 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 17:00:17 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_all_helper2(t_main *main)
{
	int	i;

	i = -1;
	if (main->map_cpy)
	{
		while (main->map_cpy[++i])
			free(main->map_cpy[i]);
		free(main->map_cpy);
	}
	if (main->player_pos)
		free(main->player_pos);
	if (main->calc)
		free(main->calc);
}

void	free_all_helper(t_main *main)
{
	int	i;

	i = -1;
	if (main->n_path)
		free(main->n_path);
	if (main->s_path)
		free(main->s_path);
	if (main->w_path)
		free(main->w_path);
	if (main->e_path)
		free(main->e_path);
	if (main->f_color)
		free(main->f_color);
	if (main->c_color)
		free(main->c_color);
	if (main->player_update)
		free(main->player_update);
	if (main->map)
	{
		while (main->map[++i])
			free(main->map[i]);
		free(main->map);
	}
}

void	free_all(t_main *main)
{
	t_omap	*cur;

	if (main)
	{
		if (main->omap)
		{
			cur = main->omap;
			while (cur)
			{
				main->omap = main->omap->next;
				free(cur->row);
				free(cur);
				cur = main->omap;
			}
		}
		free_all_helper(main);
		free_all_helper2(main);
		destroy_mlx(main);
		free(main);
	}
	exit(1);
}
