#include "../minishell.h"

int	ft_condition_check2(char *str, int i, char c, int flag)
{
	if (flag == 5 && str[i] == '\\' &&
		(str[i + 1] == '$' || str[i + 1] == '\"' ||
			str[i + 1] == '`' || str[i + 1] == '\\') && c != '\'')
		return (1);
	if (flag == 6 && str[i] == '=' &&
		ft_search_char_equal_before_space_or_qoute(str, i, 1))
		return (1);
	if (flag == 7 && str[i] == '$' &&
			(str[i + 1] == '\"' || str[i + 1] == '\''))
		return (1);
	if (flag == 8 && str[i] == '$' &&
		((i && str[i - 1] != '\\') ||
			i == 0) && str[i + 1] == '?')
		return (1);
	return (0);
}
