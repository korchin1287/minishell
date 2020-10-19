#include "../minishell.h"

int	status_return(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		if (WTERMSIG(status) == 3)
			return (131);
	}
	return (WEXITSTATUS(status));
}
