/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbui-vu <hbui-vu@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:30:29 by hbui-vu           #+#    #+#             */
/*   Updated: 2023/08/31 10:30:44 by hbui-vu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	reset_sprite_search(t_main *main)
{
	t_sprite	*sp;
	int			i;
	
	sp = main->sprite;
	i = 0;
	while (i < main->sprite_num)
	{
		sp[i].render = 0;
		sp[i].start_col = -1;
		sp[i].end_col = -1;
		i++;
	}
}

void	test_sprite(t_main *main)
{
	t_sprite	*sp;
	int			i;

	sp = main->sprite;
	i = 0;

	sp[i].render = 1;
	sp[i].spx = (sp[i].sp_gridx + .5) * UPG;
	sp[i].spy = (sp[i].sp_gridy + .5) * UPG;
	sp[i].vx = sp[i].spx - main->calc->px;
	sp[i].vy = sp[i].spy - main->calc->py;
	sp[i].sp_dist = 181.0193359838;
	sp[i].vangle = atan2(-sp[i].vy, sp[i].vx);
	if (sp[i].vangle < 0)
		sp[i].vangle += main->calc->rad_360;
	else if (sp[i].vangle > main->calc->rad_360 
		|| ch_num(sp[i].vangle, main->calc->rad_360))
		sp[i].vangle -= main->calc->rad_360;
	printf("pdir: %lf, fov: %lf\n", main->calc->pdir, main->calc->fov);
	sp[i].rel_vangle = main->calc->pdir + (main->calc->fov / 2) - sp[i].vangle;
	if (sp[i].rel_vangle < 0)
		sp[i].rel_vangle += main->calc->rad_360;
	else if (sp[i].rel_vangle > main->calc->rad_360 
		|| ch_num(sp[i].rel_vangle, main->calc->rad_360))
		sp[i].rel_vangle -= main->calc->rad_360;
	sp[i].plnx = sp[i].rel_vangle * main->calc->col_to_fov_ratio;
	sp[i].sp_size = (main->calc->height_ratio) / sp[i].sp_dist;
	printf("px: %lf py: %lf\n", main->calc->px, main->calc->py);
	print_sprite(sp);
}



void	sp_find_pix_color(t_pix *pix, t_main *main)
{
	int		offset;
	void	*addr;
	t_img	texture;

	texture = main->img_no_wall;
	offset = pix->y * texture.line_length + pix->x * (texture.bpp / 8);
	addr = texture.addr + offset;
	pix->r = *((uint32_t *)addr) >> 16;
	pix->g = *((uint32_t *)addr) >> 8 & 255;
	pix->b = *((uint32_t *)addr) & 255;
}

void	sp_get_nearest_pix(t_point *p, t_main *main)
{
	p->x1 = (int)p->orig_x;
	if (p->x1 == TW - 1)
		p->x2 = p->x1;
	else
		p->x2 = p->x1 + 1;
	p->y1 = (int)p->orig_y;
	if (p->y1 == TH - 1)
		p->y2 = p->y1;
	else
		p->y2 = p->y1 + 1;
	p->p1.x = p->x1;
	p->p1.y = p->y1;
	p->p2.x = p->x1;
	p->p2.y = p->y2;
	p->p3.x = p->x2;
	p->p3.y = p->y1;
	p->p4.x = p->x2;
	p->p4.y = p->y2;
	sp_find_pix_color(&p->p1, main);
	sp_find_pix_color(&p->p2, main);
	sp_find_pix_color(&p->p3, main);
	sp_find_pix_color(&p->p4, main);
	p->x_dist = p->orig_x - (int)p->orig_x;
	p->y_dist = p->orig_y - (int)p->orig_y;
}

void	sp_interpolate(int x, int y, t_point *p, t_main *main)
{
	int		offset;
	void	*dst;

	sp_get_nearest_pix(p, main);
	p->r1 = (p->p1.r * (1 - p->x_dist)) + (p->p2.r * p->x_dist);
	p->r2 = (p->p3.r * (1 - p->x_dist)) + (p->p4.r * p->x_dist);
	p->r = (p->r1 * (1 - p->y_dist)) + (p->r2 * p->y_dist);
	p->g1 = (p->p1.g * (1 - p->x_dist)) + (p->p2.g * p->x_dist);
	p->g2 = (p->p3.g * (1 - p->x_dist)) + (p->p4.g * p->x_dist);
	p->g = (p->g1 * (1 - p->y_dist)) + (p->g2 * p->y_dist);
	p->b1 = (p->p1.b * (1 - p->x_dist)) + (p->p2.b * p->x_dist);
	p->b2 = (p->p3.b * (1 - p->x_dist)) + (p->p4.b * p->x_dist);
	p->b = (p->b1 * (1 - p->y_dist)) + (p->b2 * p->y_dist);
	offset = y * main->img.line_length + x * (main->img.bpp / 8);
	dst = main->img.addr + offset;
	*(unsigned int *)dst = encode_rgb((int)p->r, (int)p->g, (int)p->b);
}

void	render_sprite(t_sprite *sp, t_main *main)
{
	int			row;
	int			col;
	int			start;
	int			begin;
	int			stop;
	t_point		p;

	test_sprite(main);
	row = 0;
	col = (int)(sp->plnx - sp->sp_size / 2);
	start = (int)(main->calc->midpt - (sp->sp_size / 2));
	begin = start;
	stop = (int)(start + sp->sp_size);
	if (stop >= WIN_HEIGHT)
		stop = WIN_HEIGHT - 1;
	p.scale = sp->sp_size / TH;
	// printf("info: col: %i, start: %i, stop: %i, scale: %lf\n", col, start, stop, p.scale);
	while (col < (int)sp->sp_size)
	{
		if (col >= sp->start_col && col <= sp->end_col)
		{
			while (row < (int)sp->sp_size && begin <= stop)
			{
				if (start >= 0)
				{
					p.orig_x = col / p.scale;
					if (p.orig_x > (double)TW - 1)
						p.orig_x = (double)TW - 1;
					p.orig_y = row / p.scale;
					if (p.orig_y > (double)TH - 1)
						p.orig_y = (double)TH - 1;
					sp_interpolate(col, start, &p, main);
				}
				row++;
				begin++;
			}
		}
		col++;
		begin = start;
	}
}

// void	search_sprite(int row, int col, t_main *main)
// {
// 	t_sprite	*sp;
// 	int			i;

// 	sp = main->sprite;
// 	i = 0;
// 	while (i < main->sprite_num)
// 	{
// 		if (ch_num(sp[i].x, (double)col) && ch_num(sp[i].y, (double)row))
// 		{
// 			if (sp[i].start_col == -1)
// 				sp[i].start_col = main->calc->x;
// 			sp[i].end_col = main->calc->x;
// 			if (sp[i].render == 0)
// 			{
// 				sp[i].render = 1;
// 				sp[i].spx = (sp[i].sp_gridx + .5) * UPG;
// 				sp[i].spy = (sp[i].sp_gridy + .5) * UPG;
// 				sp[i].vx = sp[i].spx - main->calc->px;
// 				sp[i].vy = sp[i].spy - main->calc->py;
// 				sp[i].vangle = atan2(-sp[i].vy, sp[i].vx);
// 				if (sp[i].vangle < 0)
// 					sp[i].vangle += main->calc->rad_360;
// 				else if (sp[i].vangle > main->calc->rad_360 
// 					|| ch_num(sp[i].vangle, main->calc->rad_360))
// 					sp[i].vangle -= main->calc->rad_360;
// 				sp[i].rel_vangle = main->calc->pdir + (c->FOV / 2) - sp[i].vangle;
// 				if (sp[i].rel_vangle < 0)
// 					sp[i].rel_vangle += main->calc->rad_360;
// 				else if (sp[i].rel_vangle > main->calc->rad_360 
// 					|| ch_num(sp[i].rel_vangle, main->calc->rad_360))
// 					sp[i].rel_vangle -= main->calc->rad_360;
// 				sp[i].plnx = sp[i].rel_vangle * main->calc->col_to_fov_ratio;
// 				sp[i].sp_size = (main->calc->height_ratio) / sp[i].sp_dist;
// 			}
// 			return ;
// 		}
// 		i++;
// 	}
// }
