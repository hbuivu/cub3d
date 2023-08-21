/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:27:01 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/20 15:28:07 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	error_check(int argc, char **argv)
{
	if (argc != 2)
	{
		perror("Error\n wrong number of arguments");
		exit (0);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		perror("Error\n require .cub argument");
		exit(0);
	}
}

void	return_error(t_main *main, int err_msg)
{
	t_omap	*cur;
	int		i;

	i = -1;
	if (err_msg == IDENT_ERR)
		perror("incorrect identifier");
	if (err_msg == NBR_IDENT_ERR)
		perror("incorrect number of identifier");
	if (err_msg == XPM_ERR)
		perror("require .xpm file");
	if (err_msg == GNL_ERR)
		perror("gnl didn't get string");
	if (err_msg == PLAYER_ERR)
		perror("incorrect number of players");
	if (err_msg == MALLOC_ERR)
		perror("could not malloc");
	if (err_msg == MAP_ERR)
		perror("error in map");
	if (err_msg == MLX_ERR)
		perror("missing map components");
	if (err_msg == OPEN_ERR)
		perror("not a file");
	if (err_msg == WALL_ERR)
		perror("map not surrounded by walls");
	if (err_msg == NONE)
		perror("the end");
	if (err_msg == IMG_ERR)
		perror("error saving image");
	if (err_msg == COMMA_ERR)
		perror("wrong number of commas");
	if (err_msg == INT_ERR)
		perror("require integer");
	if (err_msg == COMMA_PLACE_ERR)
		perror("wrong placement of comma");
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
		if (main->player_pos)
			free(main->player_pos);
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
		if (main->map)
		{
			while (main->map[++i])
				free(main->map[i]);
			free(main->map);
		}
		if (main->calc)
			free(main->calc);
		free(main);
	}
	exit(1);
}