#include "../fdf.h"

void	free_matrix(char **matrix)
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

void	free_matrix_t_data(t_data *matrix)
{
	size_t	i;

	i = 0;
	while (matrix->map_info[i])
	{
		free(matrix->map_info[i]);
		i++;
	}
	free(matrix->map_info);
	matrix->map_info = NULL;
}

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int		i;

	if (x < WIN_X && x >= 0 && y >= 0 && y < WIN_Y)
	{
		i = (x * data->bits_per_pixel / 8) + (y * data->line_length);
		data->addr[i] = color;
		data->addr[++i] = color >> 8;
		data->addr[++i] = color >> 16;
	}
}

int	ft_min(int first, int second)
{
	if (first > second)
		return (first);
	return (second);
}