#include "../minishell.h"

static int	ft_len_qoutes(char *str, char c, int *i)
{
	int len;

	len = 0;
	(*i)++;
	while (str[*i] != c && str[*i] != '\0')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '$' ||
			str[*i + 1] == '\"' || str[*i + 1] == '`' ||
				str[*i + 1] == '\\') && c != '\'')
		{
			len += 2;
			*i += 2;
		}
		else
		{
			len++;
			(*i)++;
		}
	}
	(*i)++;
	return (len);
}

static int	ft_len_arg_loop(char *str, int *i)
{
	int len;

	len = 0;
	while (ft_condition_check(str, i, 1))
	{
		if (ft_condition_check(str, i, 0))
		{
			*i += 2;
			len += 2;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			len += ft_len_qoutes(str, str[*i], i) + 2;
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

int			ft_len_arg(t_shell *shell, t_data *data, char *str, int *i)
{
	int len;
	int tmp;

	len = ft_len_arg_loop(str, i);
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == ';' || str[*i] == '|')
	{
		if (!(tmp = ft_check_arg(data, str, i)))
		{
			ft_exitstatus(shell, 258);
			return (-1);
		}
	}
	if (str[*i] == '|' && str[*i + 1] != '|' && str[*i + 1])
		(*i)++;
	return (len);
}
