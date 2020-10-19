#include "libft.h"

size_t	ft_strlen_3(const char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}
