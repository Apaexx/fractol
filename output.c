/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:37:37 by ynejmi            #+#    #+#             */
/*   Updated: 2021/09/13 15:37:38 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	putpixel(t_fract *fract, int x, int y, t_color color)
{
	int	i;

	i = (x * fract->img->bitsperpixel / 8)
		+ (y * fract->img->linesize);
	fract->img->data_addr[i] = color.channel[3];
	fract->img->data_addr[++i] = color.channel[2];
	fract->img->data_addr[++i] = color.channel[1];
	fract->img->data_addr[++i] = color.channel[0];
}

t_color	itoco(int i, t_fract *fract)
{
	t_color	color;
	double	t;

	t = (double)i / fract->max_i;
	color.channel[0] = 0;
	color.channel[((0 + fract->color_shift) % 3) + 1] = (int8_t)(9 * (1 - t)
			* pow(t, 3) * 255);
	color.channel[((1 + fract->color_shift) % 3) + 1] = (int8_t)(15 * pow((1
					- t), 2) * pow(t, 2) * 255);
	color.channel[((2 + fract->color_shift) % 3) + 1] = (int8_t)(8.5 * pow((1
					- t), 3) * t * 255);
	return (color);
}

void	drawfract(t_fract *fract)
{
	int		x;
	int		y;
	t_color	color;

	fract->factor = init_complex((fract->max.a - fract->min.a) / (WIDTH - 1),
			(fract->max.b - fract->min.b) / (HEIGHT - 1));
	y = 0;
	while (y < HEIGHT)
	{
		fract->c.b = fract->max.b - y * fract->factor.b;
		x = 0;
		while (x < WIDTH)
		{
			fract->c.a = fract->min.a + x * fract->factor.a;
			color = itoco(fract->func(fract), fract);
			putpixel(fract, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fract->mlx, fract->window, fract->img->image, 0, 0);
}
