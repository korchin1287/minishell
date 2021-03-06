#include "libft.h"

static	void	ft_nb(int n, char *str, int len)
{
	int				i;
	unsigned int	nb;

	i = len;
	if (n < 0)
	{
		str[0] = '-';
		nb = (unsigned int)-n;
		len--;
	}
	else
	{
		nb = (unsigned int)n;
	}
	str[i] = '\0';
	while (len-- > 0)
	{
		i--;
		str[i] = nb % 10 + 48;
		nb = nb / 10;
	}
}

char			*ft_itoa(int n)
{
	int		nn;
	int		i;
	char	*res;

	i = 0;
	nn = n;
	while (nn != 0)
	{
		nn = nn / 10;
		i++;
	}
	if (n <= 0)
		i++;
	res = (char*)ft_malloc(sizeof(*res), i + 1);
	ft_nb(n, res, i);
	return (res);
}
