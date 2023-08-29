/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_macros.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:19:29 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/28 12:19:29 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/* KEYS */
# define LEFT_KEY				123
# define RIGHT_KEY				124
# define A_KEY					0
# define S_KEY					1
# define D_KEY					2
# define W_KEY					13
# define ESC 					53

// /* LINUX KEYS */
// # define LEFT_KEY				XK_Left
// # define RIGHT_KEY				XK_Right
// # define A_KEY					XK_a
// # define S_KEY					XK_s
// # define D_KEY					XK_d
// # define W_KEY					XK_w
// # define ESC 					XK_Escape

/* DIMENSIONS */
# define TW						64	//texture width
# define TH						64  //texture height
# define WIN_WIDTH				1920
# define WIN_HEIGHT				1024

/* GAME ELEMENTS */
# define WALK					8
# define RUN					32
# define WALL_BUFF				10
# define ANGLE_ROT				0.0349066
# define FOV					66

/* MINIMAP */
# define MM_PLAYER				0XFF5733
# define MM_WALL				0XF08080
# define MM_DOOR				0X8B4513
# define MM_SPRITE				0Xca8dfd
# define MM_FLOOR				0x00FFFF
# define MM_TILE_SIZE			16

/* sprite */
# define SH						16 // sprite width
# define SW						16 // sprite width

#endif
