/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:29:01 by micongiu          #+#    #+#             */
/*   Updated: 2024/09/09 15:52:56 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			copy[i][j].y = (int)round((-1 * copy[i][j].z) + (tmp_x + tmp_y)
					* 0.500000194);
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

void	bresenhamline_x(t_data *img, t_m_info **copy, int j, int i)
{
	t_draw_var	var;

	var.dx = abs(copy[i][j + 1].x - copy[i][j].x);
	var.dy = abs(copy[i][j + 1].y - copy[i][j].y);
	if (copy[i][j].x < copy[i][j + 1].x)
		var.sign_x = 1;
	else
		var.sign_x = -1;
	if (copy[i][j].y < copy[i][j + 1].y)
		var.sign_y = 1;
	else
		var.sign_y = -1;
	var.error[0] = var.dx - var.dy;
	var.x_print = copy[i][j].x;
	var.y_print = copy[i][j].y;
	var.percent = 0.0;
	while (var.x_print != copy[i][j + 1].x || var.y_print != copy[i][j + 1].y)
	{
		pixel_put(img, var.x_print, var.y_print, get_color_x(copy, var, j, i));
		var.error[1] = 2 * var.error[0];
		ft_error_update(&var);
	}
}

void	bresenhamline_y(t_data *img, t_m_info **copy, int j, int i)
{
	t_draw_var	var;

	var.dx = abs(copy[i + 1][j].x - copy[i][j].x);
	var.dy = abs(copy[i + 1][j].y - copy[i][j].y);
	if (copy[i][j].x < copy[i + 1][j].x)
		var.sign_x = 1;
	else
		var.sign_x = -1;
	if (copy[i][j].y < copy[i + 1][j].y)
		var.sign_y = 1;
	else
		var.sign_y = -1;
	var.error[0] = var.dx - var.dy;
	var.x_print = copy[i][j].x;
	var.y_print = copy[i][j].y;
	var.percent = 0.0;
	while (var.x_print != copy[i + 1][j].x || var.y_print != copy[i + 1][j].y)
	{
		pixel_put(img, var.x_print, var.y_print, get_color_y(copy, var, j, i));
		var.error[1] = 2 * var.error[0];
		ft_error_update(&var);
	}
}

void	ft_draw(t_data *img)
{
	size_t		i;
	size_t		j;
	t_m_info	**copy_map;

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
				bresenhamline_x(img, copy_map, j, i);
			if (i < img->collon - 1)
				bresenhamline_y(img, copy_map, j, i);
			j++;
		}
		i++;
	}
	free_matrix((void **)copy_map);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}
