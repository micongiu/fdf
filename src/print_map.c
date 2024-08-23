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
			copy[i][j].x = (tmp_x - tmp_y) * cos(0.523599);
			copy[i][j].y = (tmp_x + tmp_y) * sin(0.523599) - copy[i][j].z;
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

void	ft_draw(t_data *img)
{
	size_t		i;
	size_t		j;
	t_m_info 	**copy;

	i = 0;
	j = 0;
	copy = ft_mem(img, copy);
	print_isometric(copy, img);
	ft_help(img, copy);
	ft_bzero(img->addr, WIN_X * WIN_Y * (img->bits_per_pixel / 8));
	while (copy[i])
	{
		j = 0;
		while (j != img->row - 1)
		{
			// ft_printf("x = %d \t y = %d\n", copy[i][j].x, copy[i][j].y);
			xiaolin_wu(j, copy[i], img);
			xiaolin_wu_2(j, i, copy, img);
			j++;
		}
		i++;
	}
	free_matrix_t_m_info(copy);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}
