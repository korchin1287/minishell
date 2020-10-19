#include "libft.h"

void	ft_free_null(void **var)
{
	void **ptr;

	ptr = var;
	free(*ptr);
	*ptr = NULL;
}
