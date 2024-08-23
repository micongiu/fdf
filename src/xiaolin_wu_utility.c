#include "../fdf.h"

// integer part of x
int ft_ipart(float x)
{
	return ((int)x);
}

int ft_round(float x)
{
	return ((int)(float)(x + 0.5));
}

// fractional part of x
float ft_fpart(float x)
{
	return ((float)x - (float)ft_ipart(x));
}

float ft_rfpart(float x)
{
	return (1 - ft_fpart(x));
}

float	ft_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}
