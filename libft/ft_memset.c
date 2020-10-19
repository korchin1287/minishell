#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char *)destination;
	while (n-- > 0)
	{
		*(ptr + n) = (unsigned char)c;
	}
	return (destination);
}
