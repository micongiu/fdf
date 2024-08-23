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

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}
