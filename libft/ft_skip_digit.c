#include "libft.h"

int	ft_skip_digit(char *str, int i)
{
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}
