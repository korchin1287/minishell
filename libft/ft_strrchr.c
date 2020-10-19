#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	while (i > 0)
	{
		if (str[i] == (char)ch)
		{
			break ;
		}
		i--;
	}
	if (str[i] != (char)ch)
		return (NULL);
	return ((char*)&str[i]);
}
