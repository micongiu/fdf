#include "../fdf.h"

void	print_isometric(t_m_info **copy ,t_data *img)
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

void	ft_help(t_data *img, t_m_info **copy)
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
			if (img->yes_no == 1)
			{
				copy[i][j].x *= img->zoom;
				copy[i][j].y *= img->zoom;
			}
			copy[i][j].x += img->translation_x;
			copy[i][j].y += img->translation_y;
			j++;
		}
		i++;
	}
}

static void	my_mlx_pixel_put_2(t_data *data, int x, int y, int color)
{
	int		i;

	if (x < WIN_X && y >= 0 && y < WIN_Y)
	{
		i = (x * data->bits_per_pixel / 8) + (y * data->line_length);
		data->addr[i] = color;
		data->addr[++i] = color >> 8;
		data->addr[++i] = color >> 16;
	}
}

void bresenhamLine(t_data *img, int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put_2(img, x1, y1, 0xFFFFFF);
		if (x1 == x2 && y1 == y2)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	ft_draw(t_data *img)
{
	size_t		i;
	size_t		j;
	t_m_info 	**copy;

	i = 0;
	j = 0;
	copy = ft_mem(img, copy);
	// print_isometric(copy, img);
	ft_help(img, copy);
	ft_bzero(img->addr, WIN_X * WIN_Y * (img->bits_per_pixel / 8));
	while (copy[i + 1] != NULL)
	{
		j = 0;
		while (j != img->row - 1)
		{
			// ft_printf("x = %d \t y = %d\n", copy[i][j].x, copy[i][j].y);
			// bresenhamLine(img, copy[i][j].x, copy[i][j].y, copy[i + 1][j + 1].x, copy[i + 1][j + 1].y);
			bresenhamLine(img, copy[i][j].x, copy[i][j].y, copy[i + 1][j].x, copy[i + 1][j].y);
			bresenhamLine(img, copy[i][j].x, copy[i][j].y, copy[i][j + 1].x, copy[i][j + 1].y);
			// xiaolin_wu_2(j, i, copy, img);
			j++;
		}
		i++;
	}
	free_matrix_t_m_info(copy);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}
