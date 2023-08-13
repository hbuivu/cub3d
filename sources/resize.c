#include "../include/cub3D.h"

//use bilinear interpolation to resize pixels
//assume image is 64x64 pixels

/* 
1. find which slice of wall the ray is hitting (check for x column) 
2. find the wall height (pixel height)
3. divide wall height / upg to find scale of the wall
4. 
*/

