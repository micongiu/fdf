#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

# define ON_DESTROY 17
# define WIN_X	1920
# define WIN_Y	1200
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
# define KEY_PLUS 65451
# define KEY_MINUS 65453

typedef struct s_minfo
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_m_info;

typedef struct s_data
{
	void		*img;
	void		*mlx;
	void		*mlx_win;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_m_info	**map_info;
	int			row;
	int			collon;
	double		zoom;
	int			translation_x;
	int			translation_y;
}				t_data;

typedef struct s_draw
{
	double	dx;
	double	dy;
	double	sign_x;
	double	sign_y;
	double	error[2];
	double	percent;
	int		x_print;
	int		y_print;
}				t_draw_var;

int			main(int argc, char **argv);

void		allocate_mem(char **mat, t_data *allocate);
char		**open_file(char *file_read);
char		**read_file_try(char **str_read, int fd, char *file_read);
void		store_map(char *file_read, t_data *img);
void		store_map_help(char **tmp_split, t_data *img, int i);

void		free_matrix(void **matrix);
void		ft_error(char *str);
void		pixel_put(t_data *data, int x, int y, int color);
int			ft_min(int first, int second);

int			ft_close(t_data *img);
void		ft_init(t_data *img);
int			ft_key(int key, t_data *img);

void		ft_isometric_change(t_data *img, t_m_info **copy);
void		ft_draw(t_data *img);

int 		ft_count_nb(char *mat);
t_m_info	**ft_mem(t_data *img, t_m_info **copy);
t_m_info	**ft_mem_copy(t_data *img, t_m_info **copy);
void		ft_help_c(t_data *img, t_m_info **copy);

double		ft_cent(int first, int second, int attualy);
int			get_color_x(t_m_info **copy, t_draw_var var, int j, int i);
int			get_color_y(t_m_info **copy, t_draw_var var, int j, int i);
int			ft_atoi_base(char *str);

#endif