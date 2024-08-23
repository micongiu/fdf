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
	allo = ft_count_nb(mat[i]);
	while (mat[i])
	{
		allocate->map_info[i] = (t_m_info *)ft_calloc((allo + 1), sizeof(t_m_info ));
		if (allocate->map_info[i] == NULL)
			return(free_matrix_t_data(allocate), ft_error("Error in the allocate"));
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
		free_matrix(str_read);
		exit(0);
	}
	str_return = read_file(i, str_read, fd);
	return (close(fd), str_return);
}

char	**read_file(int i, char **str_read, int fd)
{
	int		k;
	char	**tmp;

	k = 0;
	while (str_read[i] != NULL)
	{
		i++;
		str_read[i] = get_next_line(fd);
		k = -1;
		tmp = ft_calloc((i + 2), sizeof(char **));
		if (tmp == NULL)
			ft_error("Error in the allocate");
		while (++k <= i)
			tmp[k] = ft_strdup(str_read[k]);
		free_matrix(str_read);
		str_read = ft_calloc((i + 3), sizeof(char **));
		if (str_read == NULL)
			ft_error("Error in the allocate");
		k = -1;
		while (++k <= i)
			str_read[k] = ft_strdup(tmp[k]);
		free_matrix(tmp);
	}
	return (str_read);
}

void	store_map(char *file_read, t_data *img)
{
	int			i;
	int			k;
	char		**tmp_split;
	char		**matrix_fileread;

	i = -1;
	k = 0;
	matrix_fileread = open_file(file_read);
	img->map_info = NULL;
	allocate_mem(matrix_fileread, img);
	while (matrix_fileread[++i])
	{
		tmp_split = ft_split(matrix_fileread[i], ' ');
		if (tmp_split == NULL)
			ft_error("Error in the allocate");
		while (tmp_split[k])
			k++;
		free(tmp_split[k - 1]);
		tmp_split[k - 1] = NULL;
		store_map_help(tmp_split, img, i);
		free_matrix(tmp_split);
	}
	free_matrix(matrix_fileread);
}

void	store_map_help(char **tmp_split, t_data *img, int i)
{
	int		j;
	t_save	coord;
	float	x_move;
	float	y_move;
	int		tmp_x;
	int		tmp_y;

	j = 0;
	// coord.x_med_map = (float) img->collon / 2;
	// coord.x_med_screen = (float) coord.x_med_map * ((float) (WIN_Y/img->collon)/img->collon*img->zoom);
	// coord.y_med_map = (float) img->row / 2;
	// coord.y_med_screen = (float) coord.y_med_map * ((float) (WIN_Y/img->row)/img->row*img->zoom);
	// x_move = WIN_X / 2 - coord.x_med_screen;
	// y_move = WIN_Y / 2 - coord.y_med_screen;
	img->zoom = ft_min(WIN_X / img->collon / 2, WIN_Y / img->row / 2);
	while (tmp_split[j])
	{
		img->map_info[i][j].x = j * img->zoom;
		img->map_info[i][j].y = i * img->zoom;
		img->map_info[i][j].z = ft_atoi(tmp_split[j]);
		img->map_info[i][j].color = 0x00FF0000;
		j++;
	}
}
