/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliamandel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:37:35 by ynejmi            #+#    #+#             */
/*   Updated: 2021/09/13 15:37:36 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	mandelbrot(t_fract *fract)
{
	t_complex	z;
	int			i;

	i = 0;
	z = init_complex(fract->c.a, fract->c.b);
	while ((pow(z.a, 2) + pow(z.b, 2) <= 4) && i < fract->max_i)
	{
		z = init_complex(pow(z.a, 2) - pow(z.b, 2)
				+ fract->c.a, 2 * z.a * z.b + fract->c.b);
		i++;
	}
	return (i);
}

int	julia(t_fract *fract)
{
	t_complex	z;
	int			i;

	i = 0;
	z = init_complex(fract->c.a, fract->c.b);
	while ((pow(z.a, 2) + pow(z.b, 2) <= 4) && i < fract->max_i)
	{
		z = init_complex(pow(z.a, 2) - pow(z.b, 2)
				+ fract->k.a, 2 * z.a * z.b + fract->k.b);
		i++;
	}
	return (i);
}
