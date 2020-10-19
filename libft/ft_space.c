#include "libft.h"

int		ft_space(char *str, int i)
{
	while (str[i] == ' ')
	{
		i++;
	}
	return (i);
}
