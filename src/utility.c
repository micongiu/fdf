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
