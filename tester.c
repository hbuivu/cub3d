#include <stdio.h>

int	round_down(double num)
{
	return (num);
}

int	round_up(double num)
{
	return (num + 1);
}

int main(void)
{
	float a;
	float b;

	b = 2.5;
	a = round_up(b) + 2;

	printf("%lf\n", a);
}