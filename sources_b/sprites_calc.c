/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsyyida <zsyyida@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 02:32:42 by zsyyida           #+#    #+#             */
/*   Updated: 2023/08/26 12:43:18 by zsyyida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//translate sprite position to relative to camera or player
// sqrt of pl_to_sp distance not taken bc not needed bc used to find order whih stays same
static void		calc_pl_to_sp_dist(t_main *main)
{
	int i;

	i = 0;
	while (i < NUM_SPRITES)
	{
		main->pl_to_sp_dist[i] = (
		(main->calc->px / 64 - main->texture[i]->x) *
		(main->calc->px / 64 - main->texture[i]->x) +
		(main->calc->py / 64 - main->texture[i]->y) *
		(main->calc->py / 64 - main->texture[i]->y));
		i++;
	}
}


//       //transform sprite with the inverse camera  matrix
//       // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
//       // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
//       // [ planeY   dirY ]                                          [ -planeY  planeX ]
void	calc_sprite_transform(t_main *main)
{
	double inv_det;
	int sprite_screen_x;
	
	// normalized_sprite.x = sprite.x - game->player.pos.x;
	// normalized_sprite.y = sprite.y - game->player.pos.y;
	inv_det = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication
	main->texture->transform_x = inv_det * (dirY * main->texture->x - dirX * main->texture->y);
  	main->texture->transform_y = inv_det * (-planeY * main->texture->x + planeX * main->texture->y); //this is actually the depth inside the screen, that what Z is in 3D
	main->texture->sprite_screen_x = (int)((main->map_width / 2) * (1 + main->texture->transform_x / main->texture->transform_y));
}

//       //calculate height of the sprite on screen
//       //calculate lowest and highest pixel to fill in current stripe
//       //calculate width of the sprite
void	calc_sprite(t_main *main)
{   
	calc_sprite_transform(main);
	main->texture->screen_x = (int)((WIN_WIDTH / 2) *
		(1.0 + main->texture->transform_x / main->texture->transform_y));
	main->texture->sprite_height = ABS((int)(WIN_HEIGHT/(main->texture->transform_y))); //using 'transformY' instead of the real distance prevents fisheye
    main->texture->draw_start_y =  main->map_height/2 - main->texture->height / 2  ;
    if(main->texture->draw_start_y < 0)
		main->texture->draw_start_y = 0;
    main->texture->draw_end_y = main->texture->height / 2 + WIN_HEIGHT / 2;
    if(main->texture->draw_end_y >= WIN_HEIGHT / 2)
		main->texture->draw_end_y = WIN_HEIGHT / 2 - 1;
    main->texture->width = ABS( (int)(main->map_width / (main->texture->transform_y)));
    main->texture->draw_start_x = main->texture->sprite_screen_x - main->texture->width / 2;
    if(main->texture->draw_start_x < 0)
		main->texture->draw_start_x = 0;
    main->texture->draw_end_x = main->texture->width / 2 + main->texture->sprite_screen_x;
    if(main->texture->draw_end_x  >= WIN_WIDTH)
		main->texture->draw_end_x  = WIN_WIDTH - 1;
}

//       //loop through every vertical stripe of the sprite on screen
{
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
//         //the conditions in the if are:
//         //1) it's in front of camera plane so you don't see things behind you
//         //2) it's on the screen (left)
//         //3) it's on the screen (right)
//         //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) 
		  	buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
    }
  }
}

// After it all is drawn, the screen is updated, and the input keys are handled.

//     drawBuffer(buffer[0]);
//     for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()

//     //timing for input and FPS counter
//     oldTime = time;
//     time = getTicks();
//     double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
//     print(1.0 / frameTime); //FPS counter
//     redraw();

//     //speed modifiers
//     double moveSpeed = frameTime * 3.0; //the constant value is in squares/second
//     double rotSpeed = frameTime * 2.0; //the constant value is in radians/second
//     readKeys();
//     //move forward if no wall in front of you
//     if (keyDown(SDLK_UP))
//     {

// void	draw_sprite(int x, t_main *main)
// {
// 	int		row;
// 	int		start;
// 	int		stop;
// 	t_point	p;

// 	row = 0;
// 	start = (int)(round((main->calc->pln_height / 4) - (main->calc->wall_height / 4)));
// 	if (start < 0)
// 		start = 0;
// 	stop = (int)(round(start + main->calc->wall_height/2));
// 	if (stop >= main->calc->pln_height/2)
// 		stop = (main->calc->pln_height - 1)/2;
// 	p.scale = main->calc->wall_height/2 / main->calc->upg;
// 	p.orig_x = main->calc->wall_slice;
// 	while (row < (int)main->calc->wall_height/2 && start <= stop)
// 	{
// 		p.orig_y = row / p.scale;
//     // ft_pixel_put(&main->img, col, row, encode_rgb(c[0], c[1], c[2]));
// 		get_nearest_pix(&p, main);
// 		interpolate(x, start, &p, main);
// 		row++;
// 		start++;
// 	}
// }