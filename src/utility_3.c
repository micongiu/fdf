#include "../fdf.h"

int	default_color(t_data *img, int i, int k)
{
	double	cent;

	cent = ft_cent(img->min_z, img->max_z, img->map_info[i][k].z);
	if (cent < 0.2)
		return (MOONSTONE);
	else if (cent < 0.4)
		return (HONEYDREW);
	else if (cent < 0.6)
		return (VANILLA);
	else if (cent < 0.8)
		return (ATOMIC_TANGERINE);
	else
		return (SANDY_BROWN);
}

void	set_color(t_data *img, int i)
{
	int		k;

	k = 0;
	while (i < img->collon)
	{
		k = 0;
		while (k < img->row)
		{
			if (img->map_info[i][k].color == 0)
				img->map_info[i][k].color = default_color(img, i, k);
			k++;
		}
		i++;
	}
}

void	set_center(t_data *img)
{
	img->center.x_offset = round(WIN_X / 3.5);
	img->center.y_offset = round(WIN_Y / 8.5);
	img->center.scale = (ft_min((WIN_X / img->collon), (WIN_Y / img->row)));
	if (img->center.scale <= 4)
		img->center.scale = 2;
	else
		img->center.scale /= 2;
}

void	ft_error_free(char *str, void **to_free)
{
	free_matrix(to_free);
	ft_printf("%s\n", str);
	exit(0);
}
