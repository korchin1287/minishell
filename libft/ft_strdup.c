#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	str = (char*)ft_malloc(sizeof(char), (ft_strlen(src) + 1));
	if (str == NULL)
	{
		return (NULL);
	}
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
