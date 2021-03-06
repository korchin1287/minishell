#include "libft.h"

static char	*ft_trim(char *res, char *str, char trim, int len)
{
	int i;
	int k;

	i = 0;
	k = -1;
	while (++k < len)
	{
		while (str[i] == trim)
			i++;
		res[k] = str[i++];
	}
	res[k] = '\0';
	return (res);
}

char		*ft_strtrim_char(char *str, char trim, int size)
{
	char	*res;
	int		i;
	int		len;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && size--)
		while (str[i++] == trim)
			count++;
	len = ft_strlen(str) - count;
	if (!(res = (char *)ft_malloc(sizeof(res), (len + 1))))
		return (NULL);
	res = ft_trim(res, str, trim, len);
	return (res);
}
