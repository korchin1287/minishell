#include "../minishell.h"

void		ft_swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int			ft_cout_mas(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		**ft_sort_mass(char **tmp)
{
	int i;
	int j;
	int len;

	i = 0;
	len = ft_cout_mas(tmp);
	while (i < (len - 1))
	{
		j = 0;
		while (j < (len - i - 1))
		{
			if (ft_strcmp(tmp[j], tmp[j + 1]) > 0)
				ft_swap(&tmp[j], &tmp[j + 1]);
			j++;
		}
		i++;
	}
	return (tmp);
}
