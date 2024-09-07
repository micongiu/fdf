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

int	ft_atoi_base(char *str)
{
	int	result;
	int	i;

	// printf("str = %s\n", str);
	i = 0;
	result = 0;
	while (str[i] != ',')
		i++;
	// i++;
	while (str[i] && str[i] != ' ')
	{
		result *= 16;
		if (str[i] >= '0' && str[i] <= 9)
			result += str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += str[i] - 'A' + 10;
		i++;
	}
	return (result);
}