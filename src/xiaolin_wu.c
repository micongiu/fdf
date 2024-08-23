#include "../fdf.h"

void	xiaolin_wu_1(t_draw_var var, t_data *data, int x1, int y1);
void	xiaolin_wu_2(int index_y, int index_x, t_m_info **copy, t_data *data);
void	xiaolin_wu_3(t_draw_var var, t_data *data, int x2, int y2);
void	my_mlx_pixel_put(t_data *data, int x, int y);

void	xiaolin_wu(int index, t_m_info *copy, t_data *data)
{
	t_draw_var	var;

	var.dx = copy[index + 1].x - copy[index].x;
	var.dy = copy[index + 1].y - copy[index].y;
	if (var.dx == 0.0)
		var.angle = 1.0;
	else
		var.angle = var.dy / var.dx;
	var.xend = ft_round(copy[index].x);
	var.yend = copy[index].y + var.angle * (var.xend - copy[index].x);
	var.xpxl1 = var.xend;
	var.ypxl1 = ft_ipart(var.yend);
	my_mlx_pixel_put(data, var.xpxl1, var.ypxl1);
	my_mlx_pixel_put(data, var.xpxl1, var.ypxl1 + 1);
	xiaolin_wu_1(var, data, copy[index + 1].x, copy[index + 1].y);
}

void	xiaolin_wu_1(t_draw_var var, t_data *data, int x2, int y2)
{
	int	x;

	x = var.xpxl1 + 1;
	var.interse_y = var.yend + var.angle;
	var.xend = ft_round(x2);
	var.yend = y2 + var.angle * (var.xend - x2);
	var.xpxl2 = var.xend;
	var.ypxl2 = ft_ipart(var.yend);
	my_mlx_pixel_put(data, var.xpxl2, var.ypxl2);
	my_mlx_pixel_put(data, var.xpxl2, var.ypxl2 + 1);
	while (x < var.xpxl2)
	{
		my_mlx_pixel_put(data,  x, ft_ipart(var.interse_y));
		my_mlx_pixel_put(data,  x, ft_ipart(var.interse_y) + 1);
		var.interse_y += var.angle;
		x++;
	}
}

void	xiaolin_wu_2(int index_y, int index_x, t_m_info **copy, t_data *data)
{
	t_draw_var	var;

	var.dx = copy[index_y + 1][index_x].x - copy[index_y][index_x].x;
	var.dy = copy[index_y + 1][index_x].y - copy[index_y][index_x].y;
	if (var.dx == 0.0)
		var.angle = 0.0;
	else
		var.angle = var.dy / var.dx;
	var.yend = ft_round(copy[index_y][index_x].y);
	var.xend = copy[index_y][index_x].x + var.angle *
		(var.yend - copy[index_y][index_x].y);
	var.ypxl1 = var.yend;
	var.xpxl1 = ft_ipart(var.xend);
	my_mlx_pixel_put(data, var.xpxl1,   var.ypxl1);
	my_mlx_pixel_put(data, var.xpxl1 + 1, var.ypxl1);
	var.interse_x = var.xend + var.angle;
	xiaolin_wu_3(var, data, copy[index_y + 1][index_x].x,
		copy[index_y + 1][index_x].y);

}

void	xiaolin_wu_3(t_draw_var var, t_data *data, int x2, int y2)
{
	int	y;

	y = var.ypxl1 + 1;
	var.yend = ft_round(y2);
	var.xend = x2 + var.angle * (var.yend - y2);
	var.ypxl2 = var.yend;
	var.xpxl2 = ft_ipart(var.xend);
	my_mlx_pixel_put(data, var.xpxl2, var.ypxl2);
	my_mlx_pixel_put(data, var.xpxl2 + 1, var.ypxl2);
	while (y <= var.ypxl2)
	{
		my_mlx_pixel_put(data, ft_ipart(var.interse_x), y);
		my_mlx_pixel_put(data, ft_ipart(var.interse_x) + 1, y);
		var.interse_x += var.angle;
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y)
{
	char	*dst;

	if (x < WIN_X && y >= 0 && y < WIN_Y && x >= 0)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = 0x00FF0000;
	}
}
