/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student42abudhabi.ae>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:46:52 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/29 17:42:11 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/include/libft.h"
# include "structs.h"
# include "macros.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
// # include <X11/keysym.h>

/* error.c */
void	error_check(int argc, char **argv);
void	return_error(t_main *main, int err_msg);
void	destroy_mlx(t_main *main);

/* free .c*/
void	free_all(t_main *main);

/* utils.c */
void	*cub_calloc(size_t count, size_t size, t_main *main);
char	*cub_strdup(const char *s1, t_main *main);
int		ch_num(double num, double comp);

/* parse_map.c */
void	download_map(int fd, t_main *main);
void	check_map(t_omap *omap_start, t_main *main);
void	get_map(t_omap *ptr_map, t_main *main);

/* mlx_imgs.c */
void	mlx(t_main *main);
void	get_textures(t_main *main);
void	get_data_addr(t_main *main);

/* calc.c */
void	calc_step(double angle, t_calc *c);
void	init_calc(t_main *main);
void	reset_ray(t_calc *c);
void	recalc_ray(t_calc *c);

/* coord_check.c */
int	check_coord(int jump, t_main *main);

/* draw_utils.c */
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	get_nearest_pix(t_point *p, t_main *main);
void	interpolate(int x, int y, t_point *p, t_main *main);

/* draw.c */
void	draw_wall(int x, t_main *main);
void	draw_floor_ceiling(t_main *main);

/* raycasting.c */
void	calc_intercepts(t_calc *c, t_main *main);
void	raycast(t_main *main);

/* wall_collision.c */
double	check_hline(t_calc *c, t_main *main);
double	check_vline(t_calc *c, t_main *main);
double	check_line(t_calc *c, t_main *main);

/* mlx_hooks.c */
int		ft_close(t_main *main);
int		key_press(int key_code, t_main *main);

/* test*/
void	print_omap(t_omap *map);
void	print_main_map(t_main *main);
void	print_calc(t_main *main);
void	print_main(t_main *main);

/* identify.c */
t_omap	*identify(t_omap *omap, t_main *main);

/* identify_color.c */
void	floor_colour(t_main *main, char *ptr);
void	ceiling_colour(t_main *main, char *ptr);
int		*to_int(char *s, t_main *main);
void	digit_check(char *s, int i, t_main *main);
void	free_split(char **split);

/* identify path.c */
void	n_path_identity(t_main *main, char *s, char *id);
void	s_path_identity(t_main *main, char *s, char *id);
void	w_path_identity(t_main *main, char *s, char *id);
void	e_path_identity(t_main *main, char *s, char *id);

/* walled_check.c */
void	visit(t_queue *ptr, t_main *main, int x, int y);
void	check_walled_helper(t_queue *ptr, t_main *main);
void	check_walled(t_main *main);

/* walled_check_utilties.c */
t_queue	*ft_lstnew_dl(int x, int y);
t_queue	*ft_lstadd_back_dl(t_queue **queue, t_queue *new);
void	*ft_dequeue(t_queue *enqueue);
void	del(void *lst);

/* BONUSES */
/* minimap.c */
void	draw_minimap(t_main *main);
void	init_minimap(t_main *main);
int		get_color_minimap(t_main *main, int row, int col);
void	ft_pixel_box_put(t_main *main, int col, int row, int color);

/* get_textures_bonus.c*/
void	get_textures_bonus(t_main *main);
void	get_data_addr_bonus(t_main *main);

/* sprite_sort.c */
void	init_sprite(t_main *main);
void	sort_sprites(t_main *main);
void	swap_sprite(t_main *main, int a, int b);

/* sprite_draw.c */
int		slice_in_fov(t_main *main, t_sprite sprite, int x);
void	draw_sprite_slice(t_main *main, t_sprite sprite);

/* sprite_calc.c */
void	calc_pl_to_sp_dist(t_main *main);
void	calc_sprite_transform(t_main *main);
void	calc_sprite(t_main *main);

/* get_textures_bonus.c */
void	get_textures_bonus(t_main *main);
void	get_data_addr_bonus(t_main *main);
void	draw_sprite(t_main *main);

/* mlx_hooks_bonus.c */
int		mouse_move(int x, int y, t_main *main);
void	rotate(int key, t_calc *c);

#endif
