/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:11:18 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/27 23:47:24 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	slice_in_fov(t_main *main, t_sprite sprite, int x)
{
    int i;

    if (sprite->transform_y > 0 &&
			x >= 0 && x < WIN_WIDTH &&
			sprite->transform_y < main->z_buffer[x])
        i = 1;
}

void		draw_sprite_slice(t_main *main, t_sprite sprite)
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;

	x = sprite->draw_start_x;
	while (x < sprite->draw_end_x)
	{
		tex_x = (int)((x - (-sprite->width / 2 + sprite->screen_x)) *
			TW / sprite->width);
		if (slice_in_fov(main, sprite, x))
		{
			y = sprite->draw_start_y;
			while (y < sprite->draw_end_y)
			{
				tex_y = (int)((y - (-sprite->height / 2 + WIN_HEIGHT / 2)) *
					TH / sprite->height);
				// if (!(get_color(game->tex_sprite, tex_x, tex_y) & 0xff000000))
					/my_mlx_pixel_put(&(game->img), x, y,
						// get_color(game->tex_sprite, tex_x, tex_y));
				y++;
			}
		}
		x++;
	}
}

void	draw_sprites(t_main *main)
{
	// double				plane_length;
	int					sprite_idx;

	sort_sprites(main);
	sprite_idx = 0;
	while (sprite_idx < main->sprite_num)
	{
		calc_sprite(main, &sprite, main->sprites[sprite_idx]);
		draw_sprite_slice(main, main->sprites[sprite_idx]);
        sprite_idx++;
	}
}