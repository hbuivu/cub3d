#include "cubed.h"

int main(void)
{
	void	*mlx;
	t_data	img.
	void	*mlx_win;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 1920, 1080);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello!");
	mlx_loop(mlx);
}