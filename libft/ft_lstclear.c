#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *dst;

	if (!del)
		return ;
	while (*lst)
	{
		dst = *lst;
		del((*lst)->content);
		*lst = dst->next;
		free(dst);
	}
	*lst = NULL;
}
