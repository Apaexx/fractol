#include "fract.h"

int	main(int argc, char **argv)
{
	t_fract	*fract;
	void	*mlx;

	if (argc != 2 || !ft_isset(argv[1], 0))
		options_print();
	mlx = mlx_init();
	fract = init_fract(mlx, argv[1]);
	mlx_hook(fract->window, 17, 0, &ft_exit, 0);
	mlx_hook(fract->window, 2, 0, key_press, 0);
	mlx_hook(fract->window, 4, 0, scrollwheel, fract);
	drawrect(fract, 500);
	mlx_put_image_to_window(fract->mlx, fract->window, fract->img->image, 0, 0);
	mlx_loop(fract->mlx);
}

void	options_print(void)
{
	printf("%s\n%s\n", "julia", "mandelbort");
	exit(0);
}

t_fract	*init_fract(void *mlx, char *set)
{
	t_fract *fract;

	fract = malloc(sizeof(t_fract));
	fract->mlx = mlx;
	fract->window = mlx_new_window(fract->mlx, WIDTH, HEIGHT, set);
	fract->img = init_img(mlx);
	fract->max = init_complex(2, 2);
	fract->min = init_complex(-2, -2);
	return (fract);
}

t_mlx	*init_img(void *mlx)
{
	t_mlx	*img;

	img = malloc(sizeof(t_mlx));
	img->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	img->data_addr = mlx_get_data_addr(img->image,
		&img->bitsperpixel, &img->linesize, &img->endian);
	return (img);
}
