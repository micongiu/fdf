/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micongiu <micongiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:28:35 by micongiu          #+#    #+#             */
/*   Updated: 2024/09/09 14:35:02 by micongiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_close(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	free(img->mlx);
	free_matrix((void **)img->map_info);
	exit (1);
}

int	ft_key(int key, t_data *img)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(img->mlx, img->img);
		mlx_destroy_window(img->mlx, img->mlx_win);
		free(img->mlx);
		free_matrix((void **)img->map_info);
		exit (1);
	}
	if (key == KEY_LEFT)
		img->translation_x -= 10;
	if (key == KEY_RIGHT)
		img->translation_x += 10;
	if (key == KEY_UP)
		img->translation_y -= 10;
	if (key == KEY_DOWN)
		img->translation_y += 10;
	if (key == KEY_PLUS)
		img->zoom += 0.1;
	if (key == KEY_MINUS)
		img->zoom -= 0.1;
	if (img->zoom < 0)
		img->zoom = 0.1;
	ft_draw(img);
}

void	ft_init(t_data *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, WIN_X, WIN_Y, "micongiu fdf");
	img->img = mlx_new_image(img->mlx, WIN_X, WIN_Y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->zoom = 1;
	img->translation_y = 0;
	img->translation_x = 0;
	img->map_info = NULL;
}
