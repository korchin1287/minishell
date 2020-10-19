#include "libft.h"

char	**ft_two_ar_dup(char **str)
{
	int		i;
	char	**res;

	i = 0;
	while (str[i])
		i++;
	res = ft_malloc(sizeof(char *), i + 1);
	i = -1;
	while (str[++i])
		res[i] = ft_strdup(str[i]);
	res[i] = NULL;
	return (res);
}
