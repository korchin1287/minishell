#include "libft.h"

int		ft_toupper(int ch)
{
	if (ch >= 97 && ch <= 122)
		return ((ch - 97) + 65);
	return (ch);
}
