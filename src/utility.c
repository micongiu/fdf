/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:29:42 by micongiu          #+#    #+#             */
/*   Updated: 2024/09/09 15:58:41 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_matrix(void **matrix)
{
	size_t	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void	pixel_put(t_data *data, int x, int y, int color)
{
	int		i;

	if (x < WIN_X && x >= 0 && y >= 0 && y < WIN_Y)
	{
		i = (x * data->bits_per_pixel / 8) + (y * data->line_length);
		data->addr[i] = color;
		data->addr[++i] = color >> 8;
		data->addr[++i] = color >> 16;
		data->addr[++i] = 0;
	}
}

int	ft_min(int first, int second)
{
	if (first > second)
		return (first);
	return (second);
}

int	set_scale(t_data *img)
{
	int	sx;
	int	sy;
	int	scale;

	scale = 0;
	sx = (WIN_X - 200) / img->collon;
	sy = (WIN_Y - 200) / img->row;
	if (sx < sy)
		scale = sx / 2;
	else
		scale = sy / 2;
	if (scale == 0)
		return (1);
	return (scale);
}