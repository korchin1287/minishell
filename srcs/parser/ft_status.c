#include "../minishell.h"

int	ft_len_status(int *i)
{
	int k;
	int tmp;

	tmp = g_status;
	k = g_status ? 0 : 1;
	while (tmp != 0)
	{
		tmp = tmp / 10;
		k++;
	}
	*i += 2;
	return (k);
}

int	ft_get_status(t_data *data, int *l)
{
	char	*tmp;
	int		i;

	i = ft_strlen(data->out);
	tmp = ft_itoa(g_status);
	ft_strcpy(&data->out[i], tmp);
	*l += ft_strlen(tmp);
	ft_free_null((void **)&tmp);
	return (2);
}
