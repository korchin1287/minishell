#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	size_t		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char)ch)
			break ;
		i++;
	}
	if (str[i] != (char)ch)
		return (NULL);
	return ((char*)&str[i]);
}
