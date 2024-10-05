/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:29:42 by micongiu          #+#    #+#             */
/*   Updated: 2024/10/05 13:07:55 by micongiu         ###   ########.fr       */
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

void	fdf_atoi(t_data *img, char *str, int i, int j)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	if (*str == '+' || *str == '-')
	{
		if (*(str++) == '-')
			sign *= -1;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10;
		result += (*str++ - '0');
	}
	img->map_info[i][j].z = (sign * result);
	if (*str == ',' && *str)
		img->map_info[i][j].color = ft_atoi_base(str);
	return ;
}
