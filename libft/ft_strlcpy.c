#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (size != 0)
	{
		while (i < size - 1)
		{
			if ((dst[i] = src[i]) == '\0')
				break ;
			i++;
		}
	}
	if (i == size - 1)
	{
		dst[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
