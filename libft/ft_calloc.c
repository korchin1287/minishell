#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	mem;
	void	*ptr;

	mem = num * size;
	ptr = ft_malloc(sizeof(*ptr), mem);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, mem);
	return (ptr);
}
