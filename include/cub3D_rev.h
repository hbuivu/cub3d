/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_rev.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:46:52 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 17:51:56 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include "cub3D_structs.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
// # include <X11/keysym.h>

// from KEYCODES minilibx for ASDW and keycode for arrow keys
# define LEFT_KEY				123
# define RIGHT_KEY				124
# define A_KEY					0
# define S_KEY					1
# define D_KEY					2
# define W_KEY					13
# define ESC 					53

# define TW						64	// width of the texture
# define TH						64  //height of texture

# define WIN_WIDTH				1920
# define WIN_HEIGHT				1024
# define MM_PLAYER				0XFF5733
# define MM_WALL				0XF08080
# define MM_DOOR				0X8B4513
# define MM_SPRITE				0Xca8dfd
# define MM_FLOOR				0x00FFFF
# define MM_TILE_SIZE			24
# define WALK					4
# define NUM_SPRITES			2

# define RUN					32
# define WALL_BUFF				10
# define ANGLE_ROT				2
# define FOV					66

/* error.c */
void	error_check(int argc, char **argv);
void	return_error(t_main *main, int err_msg);

/* utils.c */
void	*cub_calloc(size_t count, size_t size, t_main *main);
char	*cub_strdup(const char *s1, t_main *main);
int		ch_num(double angle, double comp);

/* parse_map.c */
void	download_map(int fd, t_main *main);
void	check_map(t_omap *omap_start, t_main *main);
void	get_map(t_omap *ptr_map, t_main *main);

/* wall_collisions */
void	check_collision(int	key, t_main *main);

/* mlx_hooks.c */
int		ft_close(t_main *main);
int		key_press(int key_code, t_main *main);
int		mouse_move(int x, int y, t_main *main);

/* mlx_imgs.c */
void	mlx(t_main *main);
void	get_textures(t_main *main);
void	get_data_addr(t_main *main);
void	get_textures_bonus(t_main *main);
void	get_data_addr_bonus(t_main *main);

/* calc.c */
void	calc_step(t_main *main);
void	init_calc(t_main *main);
void	recalc(t_main *main);
void    calc_pdir_step(t_main *main);

/* coord_check.c */
int	check_coord(int jump, t_main *main);

/* draw.c */
void	draw_wall(int x, t_main *main);
void	draw_floor_ceiling(t_main *main);
void	get_nearest_pix(t_point *p, t_main *main);
void	interpolate(int x, int y, t_point *p, t_main *main);
void	draw_sprite(int x, t_main *main);

/* draw_utils.c */
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	find_pix_color(t_pix *pix, t_main *main);

/* raycasting.c */
void	raycast(t_main *main);

/* test*/
void	print_omap(t_omap *map);
void	print_main_map(t_main *main);
void	print_calc(t_main *main);
void	print_main(t_main *main);


/* identify.c */
t_omap	*identify(t_omap *omap, t_main *main);

void	floor_colour(t_main *main, char *ptr);
void	ceiling_colour(t_main *main, char *ptr);
int		*to_int(char *s, t_main *main);

void	n_path_identity(t_main *main, char *s, char *id);
void	s_path_identity(t_main *main, char *s, char *id);
void	w_path_identity(t_main *main, char *s, char *id);
void	e_path_identity(t_main *main, char *s, char *id);

void	visit(t_queue *ptr, t_main *main, int x, int y);
void	check_walled_helper(t_queue *ptr, t_main *main);
void	check_walled(t_main *main);
t_queue	*ft_lstnew_dl(int x, int y);
t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new);
void	*ft_dequeue(t_queue *enqueue);
void	del(void *lst);

void	draw_minimap(t_main *main);
void    init_minimap(t_main *main);
int 	get_color_minimap(t_main *main, int row, int col);
void	ft_pixel_box_put(t_main *main, int col, int row, int color);

#endif
