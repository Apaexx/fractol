/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:37:33 by ynejmi            #+#    #+#             */
/*   Updated: 2021/09/13 15:37:34 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	defult(t_fract *fract)
{
	fract->color_shift = 0;
	fract->is_julia_fixed = 0;
	fract->max_i = 100;
	fract->k = init_complex(-0.4, 0.6);
	fract->max = init_complex(2, 2);
	fract->min = init_complex(-2, -2);
}

t_fract	*init_fract(void *mlx, char *set)
{
	t_fract	*fract;

	fract = malloc(sizeof(t_fract));
	fract->mlx = mlx;
	fract->window = mlx_new_window(fract->mlx, WIDTH, HEIGHT, set);
	fract->img = init_img(mlx);
	defult(fract);
	if (ft_isset(set, 0) == 1)
		fract->func = &julia;
	else
		fract->func = &mandelbrot;
	mlx_hook(fract->window, 17, 0, &ft_exit, 0);
	mlx_hook(fract->window, 2, 0, key_press, fract);
	mlx_hook(fract->window, 4, 0, mouse_inp, fract);
	if (fract->func == &julia)
		mlx_hook(fract->window, 6, 0, julia_motion, fract);
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

t_complex	init_complex(double a, double b)
{
	t_complex	complex;

	complex.a = a;
	complex.b = b;
	return (complex);
}
