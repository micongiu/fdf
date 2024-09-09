/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:29:36 by micongiu          #+#    #+#             */
/*   Updated: 2024/09/09 16:01:07 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_count_nb(char *mat)
{
	int	j;
	int	allo;

	j = 0;
	allo = 0;
	while (mat[j])
	{
		if (mat[j] >= 48 && mat[j] <= 57)
		{
			allo++;
			j++;
		}
		while (mat[j] && mat[j] != ' ')
			j++;
		if (mat[j])
			j++;
	}
	return (allo);
}

t_m_info	**ft_mem(t_data *img, t_m_info **copy)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	while (img->map_info[i])
		i++;
	copy = (t_m_info **)ft_calloc((i + 1), sizeof(t_m_info *));
	if (copy == NULL)
	{
		free_matrix((void **)img->map_info);
		ft_error("Error in the allocate");
	}
	i = 0;
	while (img->map_info[i])
	{
		copy[i] = (t_m_info *)ft_calloc((img->row + 1), sizeof(t_m_info));
		if (copy == NULL)
			ft_help_c(img, copy);
		i++;
	}
	copy = ft_mem_copy(img, copy);
	ft_isometric_change(img, copy);
	return (copy);
}

t_m_info	**ft_mem_copy(t_data *img, t_m_info **copy)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	while (img->map_info[i])
	{
		j = 0;
		while (j != img->row)
		{
			copy[i][j].x = img->map_info[i][j].x;
			copy[i][j].y = img->map_info[i][j].y;
			copy[i][j].z = img->map_info[i][j].z;
			copy[i][j].color = img->map_info[i][j].color;
			j++;
		}
		i++;
	}
	return (copy);
}

void	ft_help_c(t_data *img, t_m_info **copy)
{
	free_matrix((void **)copy);
	free_matrix((void **)img->map_info);
	ft_error("Error in the allocate");
}

void	ft_error_update(t_draw_var *var)
{
	if (var->error[1] > -var->dy)
	{
		var->error[0] -= var->dy;
		var->x_print += var->sign_x;
	}
	if (var->error[1] < var->dx)
	{
		var->error[0] += var->dx;
		var->y_print += var->sign_y;
	}
}