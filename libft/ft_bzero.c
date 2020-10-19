#include "libft.h"

void	ft_bzero(char *s, int n)
{
	while (n >= 0)
	{
		((unsigned char *)s)[n--] = '\0';
	}
}
