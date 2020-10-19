#include "../minishell.h"

int		ft_check_list_for_export(t_list **list, char *str)
{
	t_list	*tmp;
	char	*tmp_2;

	tmp = *list;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if ((ft_strncmp(tmp->content, str, ft_strlen_3(str, '=')) == 0) &&
			!(ft_strncmp(tmp->content, str, ft_strlen_3(tmp->content, '='))))
		{
			if (!ft_strchr(str, '='))
				return (1);
			tmp_2 = tmp->content;
			tmp->content = ft_strdup(str);
			ft_free_null((void **)&tmp_2);
			tmp_2 = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
