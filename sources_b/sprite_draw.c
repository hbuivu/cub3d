/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:11:18 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 12:44:21 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_slice_visible(t_main *main, t_texture texture, int x)
{
    int i;

    if (main->texture->transform_y > 0 &&
			x >= 0 && x < WIN_WIDTH &&
			main->texture->transform_y < main->z_buffer[x])
        i = 1;
}

void		draw_sprite_slice(t_main *main, t_texture texture)
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;

	x = main->texture->draw_start_x;
	while (x < main->texture->draw_end_x)
	{
		tex_x = (int)((x - (-texture->width / 2 + texture->screen_x)) *
			TW / texture->width);
		if (is_stripe_visible(main, texture, x))
		{
			y = main->texture->draw_start_y;
			while (y < main->texture->draw_end_y)
			{
				tex_y = (int)((y - (-texture->height / 2 + WIN_HEIGHT / 2)) *
					TH / texture->height);
				// if (!(get_color(game->tex_sprite, tex_x, tex_y) & 0xff000000))
					/my_mlx_pixel_put(&(game->img), x, y,
						// get_color(game->tex_sprite, tex_x, tex_y));
				y++;
			}
		}
		x++;
	}
}

void		draw_sprites(t_main *main)
{
	double				plane_length;
	int					sprite_idx;
	t_texture	        s_texture;

	sort_sprites(main);
	sprite_idx = 0;
	while (sprite_idx < main->sprite_num)
	{
		calc_sprite(main, &texture, main->sprites[sprite_idx]);
		draw_sprite_slice(main, texture);
        sprite_idx++;
	}
}