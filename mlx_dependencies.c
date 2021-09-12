#include "fract.h"

void	putpixel(t_mlx *img, int x, int y)
{
	char	*dst;

	dst = img->data_addr + (x * img->bitsperpixel / 8 + y * img->linesize);
	*(unsigned int*)dst = img->color;
}

int		key_press(int keycode, t_fract *fract)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == R)
	{
		fract->max = init_complex(2, 2);
		fract->min = init_complex(-2, -2);
		drawfract(fract);
	}
	return (1);
}

double		interpolate(double end, double start, double zoom)
{
	return (end + ((start - end) / zoom));
}

int		scrollwheel(int keycode, int x, int y, t_fract *fract)
{
	t_complex	mouse;
	double		zoom;


	if (keycode == SCROLL_DOWN || keycode == SCROLL_UP)
	{
		mouse = init_complex((double)x / (WIDTH / (fract->max.a - fract->min.a))
			+ fract->min.a,
			(double)y / (HEIGHT / (fract->max.b - fract->min.b)) * -1
			+ fract->max.b);
		if (keycode == SCROLL_DOWN)
		{
			// printf("\033[1;31m");
			zoom = 0.8;
		}
		if (keycode == SCROLL_UP)
		{
			// printf("\033[1;32m");
			zoom = 1.2;
		}
		// printf("%f + %fi\nmax: %f + %fi\nmin: %f + %fi\nzoom%f\n", mouse.a, mouse.b, fract->max.a, fract->max.b, fract->min.a, fract->min.b, zoom);
		fract->max.a = interpolate(mouse.a, fract->max.a, zoom);
		fract->max.b = interpolate(mouse.b, fract->max.b, zoom);
		fract->min.a = interpolate(mouse.a, fract->min.a, zoom);
		fract->min.b = interpolate(mouse.b, fract->min.b, zoom);
		drawfract(fract);
	}
	return (1);
}

t_complex	init_complex(double a, double b)
{
	t_complex complex;

	complex.a = a;
	complex.b = b;
	return (complex);
}

int	ft_exit(void)
{
	exit(0);
}

void	drawfract(t_fract *fract)
{
	int	x;
	int	y;
	fract->factor = init_complex((fract->max.a - fract->min.a) / (WIDTH - 1),
		(fract->max.b - fract->min.b) / (HEIGHT - 1));
	// printf("\x1B[33mfactor: %f + %fi\n", fract->factor.a, fract->factor.b);
	y = 0;
	while (y < HEIGHT)
	{
		fract->c.b = fract->max.b - y * fract->factor.b;
		x = 0;
		while (x < WIDTH)
		{
			fract->c.a = fract->min.a + x * fract->factor.a;
			choose_color(fract);
			putpixel(fract->img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fract->mlx, fract->window, fract->img->image, 0, 0);
}

void	choose_color(t_fract *fract)
{
	t_complex	z;
	int			i;

	i = 0;
	z = init_complex(fract->c.a, fract->c.b);
	while ((pow(z.a, 2) + pow(z.b, 2) <= 4) && i < fract->max_i)
	{
		i++;
		z = init_complex(pow(z.a, 2) - pow(z.b, 2) + fract->c.a, 2 * z.a * z.b + fract->c.b);
	}
	itoco(i, fract);
}

void	itoco(int i, t_fract *fract)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)i / fract->max_i;
	// printf("%d\n", i);
	r = (int8_t)(9 * (1 - t) * pow(t, 3) * 255);
	g = (int8_t)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	b = (int8_t)(8.5 * pow((1 - t), 3) * t * 255);
	fract->img->color = r * 0x10000 + g * 0x100 + b;
}
