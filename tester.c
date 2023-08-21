#include <stdio.h>
#include <fcntl.h>
#include <math.h>

int	round_down(double num)
{
	return (num);
}

int	round_up(double num)
{
	return (num + 1);
}

// int main(void)
// {
// 	float a;
// 	float b;

// 	b = 2.5;
// 	a = round_up(b) + 2;

// 	printf("%lf\n", a);
// }

int main(void)
{
	// int i = open("./maps/cub3.cub", O_RDONLY);
	// printf("%i\n", i);
	// return 0;
	// int j = -1;
	// while (++j < 5)
	// 	printf("%i\n", j);
	// printf("j is: %i\n", j);
	// while (j < 10)
	// {
	// 	printf("%i\n", j);
	// 	j++;
	// }
	printf("%lf\n", ceil(639.99999999/64.0));
}