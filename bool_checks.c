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
			return (1);
		i++;
	}
	if (!rec)
		return (ft_isset(str, 1));
	return (0);
}
