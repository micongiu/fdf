#include "../fdf.h"

double	ft_cent(int first, int second, int attualy)
{
	if (second - first == 0)
		return (1.0);
	return ((attualy - first) / (second - first));
}

int	find_bri(int first, int second, double percent)
{
	return ((int)((1 - percent) * first + percent * second));
}

int	get_color_x(t_m_info **copy, t_draw_var var, int j, int i)
{
	int		red;
	int		green;
	int		blue;
	double	percent;

	if (copy[i][j].color == copy[i][j + 1].color)
		return (copy[i][j].color);
	if (var.dx > var.dy)
		percent = ft_cent(copy[i][j].x, copy[i][j + 1].x, var.x_print);
	else
		percent = ft_cent(copy[i][j].y, copy[i][j + 1].y, var.y_print);
	red = find_bri((copy[i][j].color >> 16) & 0xFF,
					(copy[i][j + 1].color >> 16) & 0xFF, percent);
	green = find_bri((copy[i][j].color >> 8) & 0xFF,
					(copy[i][j + 1].color >> 8) & 0xFF, percent);
	blue = find_bri(copy[i][j].color & 0xFF,
					copy[i][j + 1].color & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

int	get_color_y(t_m_info **copy, t_draw_var var, int j, int i)
{
	int		red;
	int		green;
	int		blue;
	double	percent;

	if (copy[i][j].color == copy[i + 1][j].color)
		return (copy[i][j].color);
	if (var.dx > var.dy)
		percent = ft_cent(copy[i][j].x, copy[i + 1][j].x, var.x_print);
	else
		percent = ft_cent(copy[i][j].y, copy[i + 1][j].y, var.y_print);
	red = find_bri((copy[i][j].color >> 16) & 0xFF,
					(copy[i + 1][j].color >> 16) & 0xFF, percent);
	green = find_bri((copy[i][j].color >> 8) & 0xFF,
					(copy[i + 1][j].color >> 8) & 0xFF, percent);
	blue = find_bri(copy[i][j].color & 0xFF,
					copy[i + 1][j].color & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

int	ft_atoi_base(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (str[i] != ',')
		i++;
	while (str[i] && str[i] != ' ')
	{
		result *= 16;
		if (str[i] >= '0' && str[i] <= 9)
			result += str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += str[i] - 'A' + 10;
		i++;
	}
	return (result);
}