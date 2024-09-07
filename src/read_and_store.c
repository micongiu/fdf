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
		allocate->map_info[i] = (t_m_info *)ft_calloc((allo + 1), sizeof(t_m_info ));
		if (allocate->map_info[i] == NULL)
			return(free_matrix((void **)allocate->map_info), ft_error("Error in the allocate"));
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
	int			k;
	char		**tmp_split;
	char		**matrix_fileread;

	i = 0;
	k = 0;
	matrix_fileread = open_file(file_read);
	img->map_info = NULL;
	allocate_mem(matrix_fileread, img);
	while (matrix_fileread[i])
	{
		tmp_split = ft_split(matrix_fileread[i], ' ');
		if (tmp_split == NULL)
			ft_error("Error in the allocate");
		while (tmp_split[k])
			k++;
		// free(tmp_split[k - 1]);
		// tmp_split[k - 1] = NULL;
		store_map_help(tmp_split, img, i);
		free_matrix((void **)tmp_split);
		i++;
	}
	free_matrix((void **)matrix_fileread);
}

void	store_map_help(char **tmp_split, t_data *img, int i)
{
	int		j;
	float	scale;
	int	x_offset;
	int	y_offset;
	t_save	coord;

	j = 0;
	// x_offset = (WIN_X / (img->row / 5));
	// y_offset = (WIN_Y / (img->row * img->row * 2));
	x_offset = ((WIN_X / 2) / 4 - (img->collon / 2));
	y_offset = ((WIN_Y / 2) / 4 - (img->row / 2));
	scale = ft_min(round(WIN_X / img->collon / 2),
			round(WIN_Y / img->row / 2));
	// printf("scale = %f\n", scale);
	while (tmp_split[j])
	{
		img->map_info[i][j].x = j * 55;
		img->map_info[i][j].y = i * 55;
		img->map_info[i][j].x += x_offset;
		img->map_info[i][j].y += y_offset;
		img->map_info[i][j].z = ft_atoi(tmp_split[j]);
		img->map_info[i][j].color = ft_atoi_base(tmp_split[j]);
		printf("%d %d\n", img->map_info[i][j].z, img->map_info[i][j].color);
		j++;
	}
}
