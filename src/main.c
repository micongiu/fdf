#include "../fdf.h"

int	main(int argc, char **argv)
{
	t_data		img;

	if (WIN_Y < 100 || WIN_X < 100)
		ft_error("Don't touch the code or I'll cut off your hands!\n");
	if (argc != 2)
		ft_error("Launch the program with ./fdf <name_map>");
	if (ft_strnstr(argv[1], ".fdf", ft_strlen_lib(argv[1])) == NULL)
		ft_error("Use only .fdf file");
	ft_init(&img);
	store_map(argv[1], &img);
	ft_draw(&img);
	mlx_hook(img.mlx_win, ON_DESTROY, 0, ft_close, &img);
	mlx_hook(img.mlx_win, 2, 1L << 0, ft_key, &img);
	mlx_loop(img.mlx);
}
