#include "libft.h"

void	*ft_malloc(size_t type_size, size_t size)
{
	void *ptr;

	if ((ptr = malloc(type_size * size)) == NULL)
	{
		write(2, "malloc error\n", 14);
		exit(2);
	}
	return (ptr);
}
