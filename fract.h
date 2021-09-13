/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:37:44 by ynejmi            #+#    #+#             */
/*   Updated: 2021/09/13 15:49:29 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H
# define FRACT_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "key_macos.h"
# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_mlx {
	void		*image;
	char		*data_addr;
	int			linesize;
	int			bitsperpixel;
	int			endian;
}				t_mlx;

typedef struct s_complex
{
	double		a;
	double		b;
}				t_complex;

typedef struct s_color
{
	int8_t		channel[4];
}				t_color;

typedef int	t_shabalido;

typedef struct s_fract
{
	t_mlx		*img;
	void		*window;
	void		*mlx;
	int			color_shift;
	t_complex	min;
	t_complex	max;
	t_complex	c;
	t_complex	k;
	t_complex	factor;
	t_shabalido (*func)(struct s_fract	*fract);
	int			max_i;
	int			is_julia_fixed;
}				t_fract;

void			options_print(void);
void			defult(t_fract *fract);
int				mandelbrot(t_fract *fract);
int				julia(t_fract *fract);
void			putpixel(t_fract *fract, int x, int y, t_color color);
t_fract			*init_fract(void *mlx, char *set);
t_mlx			*init_img(void *mlx);
void			drawfract(t_fract *fract);
t_color			itoco(int i, t_fract *fract);
t_complex		init_complex(double a, double b);
double			interpolate(double end, double start, double interpolation);
int				mouse_inp(int keycode, int x, int y, t_fract *fract);
int				key_press(int keycode, t_fract *fract);
int				julia_motion(int x, int y, t_fract *fract);
int				ft_exit(void);
int				ft_isset(char *str, int rec);
#endif
