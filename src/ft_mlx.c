#include "../fdf.h"

int	ft_close(t_data *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->mlx_win);
	free(env->mlx);
	free_matrix_t_data(env);
	exit (1);
}

void	ft_key_2(int key, t_data *env)
{
	if (key == KEY_LEFT)
		env->translation_x -= 10;
	if (key == KEY_RIGHT)
		env->translation_x += 10;
	if (key == KEY_UP)
		env->translation_y -= 10;
	if (key == KEY_DOWN)
		env->translation_y += 10;
	if (key == KEY_PLUS)
		env->zoom += 0.1;
	if (key == KEY_MINUS)
		env->zoom -= 0.1;
	if (env->zoom < 0)
		env->zoom = 0.1;
	if (key == KEY_PLUS || KEY_MINUS)
		env->yes_no = 1;
	ft_draw(env);
}

int	ft_key(int key, t_data *env)
{
	env->yes_no = 0;
	if (key == KEY_ESC)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->mlx_win);
		free(env->mlx);
		free_matrix_t_data(env);
		exit (1);
	}
	ft_key_2(key, env);
}

void	ft_init(t_data *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, WIN_X, WIN_Y, "micongiu fdf");
	img->img = mlx_new_image(img->mlx, WIN_X, WIN_Y);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	img->zoom = 1;
	img->translation_y = 0;
	img->translation_x = 0;
}
