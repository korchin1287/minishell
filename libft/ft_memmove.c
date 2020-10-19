#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptrd;
	unsigned char	*ptrs;

	i = 0;
	ptrd = (unsigned char *)dst;
	ptrs = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (len == 0)
		return (dst);
	if (ptrd > ptrs)
	{
		while (len-- > 0)
			ptrd[len] = ptrs[len];
	}
	else
	{
		while (i < len)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	return (dst);
}
