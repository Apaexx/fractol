#include "fract.h"

void	putpixel(t_mlx *img, int x, int y)
{
	char	*dst;

	dst = img->data_addr + (x * img->bitsperpixel / 8 + y * img->linesize);
	*(unsigned int*)dst = img->color;
}

int		key_press(int keycode)
{
	if (keycode == ESC)
		exit(0);
	return (1);
}

int		scrollwheel(int keycode, int x, int y, t_fract *fract)
{
	t_complex	mouse;
	if (keycode == SCROLL_DOWN || keycode == SCROLL_UP)
	{
		mouse = init_complex((double)x / (WIDTH / fract->max.a - fract->min.a)
			+ fract->min.a,
			(double)y / (HEIGHT / fract->max.b - fract->min.b) * -1
			+ fract->min.b);
		if (keycode == SCROLL_DOWN)
			printf("\033[1;31m");
		if (keycode == SCROLL_UP)
			printf("\033[1;32m");
		printf("%f + %fi\n", mouse.a, mouse.b); 
		fract->max.a = mouse.a 
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

void	drawrect(t_fract *fract, int rec)
{
	int	centerx;
	int	centery;
	int	y;
	int	x;

	centerx = WIDTH / 2;
	centery = HEIGHT / 2;
	x = centerx - rec / 2;
	y = centery - rec / 2;
	fract->img->color = 0xff0000;
	while (y < centery + rec / 2)
	{
		while (x < centerx + rec / 2)
		{
			if (sqrt(pow(centerx - x, 2) + pow(centery - y, 2)) < rec / 2)
				putpixel(fract->img, x, y);
			x++;
		}
		x = centerx - rec / 2;
		y++;
	}
}
