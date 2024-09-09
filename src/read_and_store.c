/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_store.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:29:15 by micongiu          #+#    #+#             */
/*   Updated: 2024/09/09 15:58:28 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	allocate_mem(char **mat, t_data *allocate)
{
	int	i;
	int	allo;

	i = 0;
	allo = 0;
	while (mat[i])
		i++;
	allocate->map_info = (t_m_info **)ft_calloc((i + 1), sizeof(t_m_info *));
	if (allocate->map_info == NULL)
		ft_error("Error in the allocate");
	i = 0;
	allo = ft_count_nb(mat[0]);
	while (mat[i])
	{
		allocate->map_info[i] = (t_m_info *)ft_calloc((allo + 1),
				sizeof(t_m_info));
		if (allocate->map_info[i] == NULL)
			return (free_matrix((void **)allocate->map_info),
				ft_error("Error in the allocate"));
		i++;
	}
	allocate->row = allo;
	allocate->collon = i;
}

char	**open_file(char *file_read)
{
	int		fd;
	int		i;
	char	**str_read;
	char	**str_return;

	fd = open(file_read, O_RDONLY);
	i = 0;
	str_read = ft_calloc((3), sizeof(char **));
	if (str_read == NULL)
		ft_error("Error in the allocate");
	str_read[0] = get_next_line(fd);
	if (str_read[0] == NULL)
	{
		ft_printf("Error in the reading\n");
		free_matrix((void **)str_read);
		exit(0);
	}
	str_return = read_file_try(str_read, fd, file_read);
	return (close(fd), str_return);
}

char	**read_file_try(char **str_read, int fd, char *file_read)
{
	int		k;
	int		i;
	int		allo;

	k = 0;
	i = 0;
	while (str_read[0] != NULL)
	{
		free(str_read[0]);
		i++;
		str_read[0] = get_next_line(fd);
	}
	close(fd);
	free_matrix((void **)str_read);
	fd = open(file_read, O_RDONLY);
	str_read = ft_calloc((i + 2), sizeof(char **));
	if (str_read == NULL)
		ft_error("Error in the allocate");
	while (k < i)
	{
		str_read[k] = get_next_line(fd);
		k++;
	}
	return (str_read);
}

void	store_map(char *file_read, t_data *img)
{
	int			i;
	int			j;
	char		**tmp_split;
	char		**matrix_fileread;

	i = 0;
	matrix_fileread = open_file(file_read);
	allocate_mem(matrix_fileread, img);
	while (matrix_fileread[i])
	{
		j = 0;
		while (matrix_fileread[i][j])
		{
			if (matrix_fileread[i][j] == '\n')
				matrix_fileread[i][j] = '\0';
			j++;
		}
		tmp_split = ft_split(matrix_fileread[i], ' ');
		if (tmp_split == NULL)
			ft_error("Error in the allocate");
		store_map_help(tmp_split, img, i);
		free_matrix((void **)tmp_split);
		i++;
	}
	free_matrix((void **)matrix_fileread);
}

void	store_map_help(char **tmp_split, t_data *img, int i)
{
	int		j;
	double	scale;
	int		x_offset;
	int		y_offset;

	j = 0;
	x_offset = round(WIN_X / 3.5);
	y_offset = round(WIN_Y / 8.5);
	scale = (ft_min((WIN_X / img->collon), (WIN_Y / img->row)));
	if (scale <= 4)
		scale = 2;
	else
		scale /= 2;
	while (tmp_split[j])
	{
		img->map_info[i][j].x = (j * scale) + x_offset;
		img->map_info[i][j].y = (i * scale) + y_offset;
		img->map_info[i][j].z = ft_atoi(tmp_split[j]);
		img->map_info[i][j].color = ft_atoi_base(tmp_split[j]);
		j++;
	}
}
