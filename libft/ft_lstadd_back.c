#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *dst;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	dst = ft_lstlast(*lst);
	dst->next = new;
}
