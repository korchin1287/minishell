#include "../minishell.h"

void	ft_free_str(char ***str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(*str))
		return ;
	while ((*str)[i])
	{
		tmp = (*str)[i];
		i++;
		free(tmp);
		tmp = NULL;
	}
	free(*str);
	*str = NULL;
}
