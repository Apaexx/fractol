/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:37:40 by ynejmi            #+#    #+#             */
/*   Updated: 2021/09/13 15:37:41 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	incremax_i(int keycode, t_fract *fract)
{
	if (keycode == PLUS || keycode == NUM_PAD_PLUS)
	{
		if (fract->max_i < 50)
			fract->max_i++;
		else if (fract->max_i < 1e9)
			fract->max_i = (int)fract->max_i * 1.05;
	}
	else
	{
		if (fract->max_i > 50)
			fract->max_i = (int)fract->max_i * 0.95;
		else if (fract->max_i > 1)
			fract->max_i--;
	}
	drawfract(fract);
}

int	key_press(int keycode, t_fract *fract)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == R)
	{
		defult(fract);
		drawfract(fract);
	}
	if (keycode == C)
	{
		fract->color_shift = (fract->color_shift + 1) % 3;
		drawfract(fract);
	}
	if (keycode == SPACE)
		fract->is_julia_fixed = !fract->is_julia_fixed;
	if (keycode == PLUS || keycode == NUM_PAD_PLUS
		|| keycode == MINUS || keycode == NUM_PAD_MINUS)
		incremax_i(keycode, fract);
	return (1);
}

double	interpolate(double end, double start, double interpolation)
{
	return (end + ((start - end) * interpolation));
}

int	mouse_inp(int keycode, int x, int y, t_fract *fract)
{
	t_complex	mouse;
	double		zoom;
	double		interpolation;

	if (keycode == MOUSE_LEFT)
		fract->is_julia_fixed = !fract->is_julia_fixed;
	if (keycode == SCROLL_DOWN || keycode == SCROLL_UP)
	{
		mouse = init_complex((double)x / (WIDTH / (fract->max.a - fract->min.a))
				+ fract->min.a,
				(double)y / (HEIGHT / (fract->max.b - fract->min.b)) * -1
				+ fract->max.b);
		if (keycode == SCROLL_DOWN)
			zoom = 0.8;
		else
			zoom = 1.2;
		interpolation = 1 / zoom;
		fract->max.a = interpolate(mouse.a, fract->max.a, interpolation);
		fract->max.b = interpolate(mouse.b, fract->max.b, interpolation);
		fract->min.a = interpolate(mouse.a, fract->min.a, interpolation);
		fract->min.b = interpolate(mouse.b, fract->min.b, interpolation);
		drawfract(fract);
	}
	return (1);
}

int	julia_motion(int x, int y, t_fract *fract)
{
	if (fract->is_julia_fixed)
		fract->k = init_complex(
				4 * ((double)x / WIDTH - 0.5),
				4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
	drawfract(fract);
	return (1);
}
