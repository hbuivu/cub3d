/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:11:15 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/21 10:34:22 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//combine textures and mlx.c
//what about alpha channel
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return (red << 16 | green << 8 | blue);
}

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = y * img->line_length + x * (img->bpp / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}
