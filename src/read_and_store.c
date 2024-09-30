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
	set_center(allocate);
}

char	**read_file(char **str_read, int fd, char *file_read)
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
	str_return = read_file(str_read, fd, file_read);
	return (close(fd), str_return);
}

void	store_map_help(char **tmp_split, t_data *img, int i)
{
	int	j;
	int	k;

	j = 0;
	while (tmp_split[j])
	{
		img->map_info[i][j].x = (j * img->center.scale) + img->center.x_offset;
		img->map_info[i][j].y = (i * img->center.scale) + img->center.y_offset;
		img->map_info[i][j].z = ft_atoi(tmp_split[j]);
		k = 0;
		// while (tmp_split[j][k] && tmp_split[j][k] != ' ')
		// {
		// 	if (tmp_split[j][k] == ',')
		// 	{
		// 		img->map_info[i][k].color = ft_atoi_base(tmp_split[j]);
		// 		break ;
		// 	}
		// 	k++;
		// }
		img->map_info[i][j].color = ft_atoi_base(tmp_split[j]);
		if (img->map_info[i][j].z > img->max_z)
			img->max_z = img->map_info[i][j].z;
		if (img->map_info[i][j].z < img->min_z)
			img->min_z = img->map_info[i][j].z;
		j++;
	}
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
		tmp_split = ft_split(matrix_fileread[i], ' ');
		if (tmp_split == NULL)
			ft_error_free("Error in the allocate", (void **)matrix_fileread);
		store_map_help(tmp_split, img, i);
		free_matrix((void **)tmp_split);
		i++;
	}	
	set_color(img, 0);
}
