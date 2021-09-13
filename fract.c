/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:37:26 by ynejmi            #+#    #+#             */
/*   Updated: 2021/09/13 15:37:27 by ynejmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

int	ft_isset(char *str, int rec)
{
	int		i;
	char	*set;

	i = 0;
	set = "Julia";
	if (rec)
		set = "Mandelbrot";
	while (str[i] == set[i])
	{
		if (!set[i])
			return (rec + 1);
		i++;
	}
	if (!rec)
		return (ft_isset(str, 1));
	return (0);
}

void	start(char *set)
{
	void	*mlx;
	t_fract	*fract;

	mlx = mlx_init();
	fract = init_fract(mlx, set);
	drawfract(fract);
	mlx_loop(fract->mlx);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !ft_isset(argv[1], 0))
		options_print();
	start(argv[1]);
}

void	options_print(void)
{
	printf("%s\n%s\n", "Julia", "Mandelbrot");
	exit(0);
}

int	ft_exit(void)
{
	exit(0);
	return (1);
}
