#include "../fdf.h"


static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
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

/*
** Draw line
*/

static void	draw_line(t_m_info first, t_m_info second, t_data *img)
{
	t_draw_var	var;
	t_m_info	tmp;
	int			error[2];

	var.diff_x = FT_ABS(second.x - first.x);
	var.diff_y = FT_ABS(second.y - first.y);
	var.sign_x = first.x < second.x ? 1 : -1;
	var.sign_y = first.y < second.y ? 1 : -1;
	error[0] = var.diff_x - var.diff_y;
	tmp = first;
	while (tmp.x != second.x || tmp.y != second.y)
	{
		my_mlx_pixel_put(img, tmp.x, tmp.y, get_color(tmp, first, second, var));
		if ((error[1] = error[0] * 2) > - var.diff_y)
		{
			error[0] -= var.diff_y;
			tmp.x += var.sign_x;
		}
		if (error[1] < var.diff_x)
		{
			error[0] += var.diff_x;
			tmp.y += var.sign_y;
		}
	}
}

/*
** Draw image
*/

void	draw(t_data *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != fdf->map->width - 1)
				draw_line(project(new_point(x, y, map), fdf),
					project(new_point(x + 1, y, map), fdf), fdf);
			if (y != fdf->map->height - 1)
				draw_line(project(new_point(x, y, map), fdf),
					project(new_point(x, y + 1, map), fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}