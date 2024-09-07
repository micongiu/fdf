#include "../fdf.h"

int ft_count_nb(char *mat)
{
	int	j;
	int	allo;

	j = 0;
	allo = 0;
	while(mat[j])
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
		copy[i] = (t_m_info *)ft_calloc((img->row + 1), sizeof(t_m_info ));
		if (copy== NULL)
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