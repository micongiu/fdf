#include "../fdf.h"

void	ft_isometric_change(t_data *img, t_m_info **copy)
{
	size_t	i;
	size_t	j;
	int		tmp_x;
	int		tmp_y;

	i = 0;
	j = 0;
	while (copy[i])
	{
		j = 0;
		while (j != img->row)
		{
			tmp_x = copy[i][j].x;
			tmp_y = copy[i][j].y;
			copy[i][j].x = (int)round((tmp_x - tmp_y) * 0.866025291);
			copy[i][j].y = (int)round((-1 * copy[i][j].z) + (tmp_x + tmp_y) * 0.500000194);
			j++;
		}
		i++;
	}
}

void	ft_move_map(t_data *img, t_m_info **copy)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (copy[i])
	{
		j = 0;
		while (j != img->row)
		{
			copy[i][j].x += img->translation_x;
			copy[i][j].y += img->translation_y;
			copy[i][j].x *= img->zoom;
			copy[i][j].y *= img->zoom;
			j++;
		}
		i++;
	}
}

void bresenhamLine_x(t_data *img, t_m_info **copy, int j, int i)
{
	t_draw_var var;

	var.dx = abs(copy[i][j + 1].x - copy[i][j].x);
	var.dy = abs(copy[i][j + 1].y - copy[i][j].y);
	var.sign_x = (copy[i][j].x < copy[i][j + 1].x) ? 1 : -1;
	var.sign_y = (copy[i][j].y < copy[i][j + 1].y) ? 1 : -1;
	var.error[0] = var.dx - var.dy;
	var.x_print = copy[i][j].x;
	var.y_print = copy[i][j].y;
	while (var.x_print != copy[i][j + 1].x || var.y_print != copy[i][j + 1].y)
	{
		my_mlx_pixel_put(img, var.x_print, var.y_print, 0xFFFFFF);
		var.error[1] = 2 * var.error[0];
		if (var.error[1] > -var.dy)
		{
			var.error[0] -= var.dy;
			var.x_print += var.sign_x;
		}
		if (var.error[1] < var.dx)
		{
			var.error[0] += var.dx;
			var.y_print += var.sign_y;
		}
	}
}

void bresenhamLine_y(t_data *img, t_m_info **copy, int j, int i)
{
	t_draw_var var;

	var.dx = abs(copy[i + 1][j].x - copy[i][j].x);
	var.dy = abs(copy[i + 1][j].y - copy[i][j].y);
	var.sign_x = (copy[i][j].x < copy[i + 1][j].x) ? 1 : -1;
	var.sign_y = (copy[i][j].y < copy[i + 1][j].y) ? 1 : -1;
	var.error[0] = var.dx - var.dy;
	var.x_print = copy[i][j].x;
	var.y_print = copy[i][j].y;
	while (1)
	{
		my_mlx_pixel_put(img, var.x_print, var.y_print, 0xFFFFFF);
		if (var.x_print == copy[i + 1][j].x && var.y_print == copy[i + 1][j].y)
			break;
		var.error[1] = 2 * var.error[0];
		if (var.error[1] > -var.dy)
		{
			var.error[0] -= var.dy;
			var.x_print += var.sign_x;
		}
		if (var.error[1] < var.dx)
		{
			var.error[0] += var.dx;
			var.y_print += var.sign_y;
		}
	}
}

void	ft_draw(t_data *img)
{
	size_t		i;
	size_t		j;
	t_m_info 	**copy_map;

	copy_map = ft_mem(img, copy_map);
	ft_move_map(img, copy_map);
	ft_bzero(img->addr, WIN_X * WIN_Y * (img->bits_per_pixel / 8));
	i = 0;
	j = 0;
	while (i < img->collon)
	{
		j = 0;
		while (j < img->row)
		{
			if (j < img->row - 1)
				bresenhamLine_x(img, copy_map, j, i);
			if (i < img->collon - 1)
				bresenhamLine_y(img, copy_map, j, i);
			j++;
		}
		i++;
	}
	free_matrix_t_m_info(copy_map);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}
