#include "libft.h"

void	ft_strcpy(char *dst, char *src)
{
	int i;

	i = -1;
	while (src[++i] != '\0')
		dst[i] = src[i];
	dst[i] = '\0';
}
