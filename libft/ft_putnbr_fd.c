#include "libft.h"

static	void	ft_nb(unsigned int n, int fd)
{
	int		i;
	char	s[10];

	i = 0;
	while (n > 0)
	{
		s[i] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	while (i > 0)
	{
		i--;
		ft_putchar_fd(s[i], fd);
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	unsigned int nb;

	if (n > 0)
	{
		ft_nb(n, fd);
	}
	else if (n < 0)
	{
		nb = (unsigned int)-n;
		ft_putchar_fd('-', fd);
		ft_nb(nb, fd);
	}
	else
	{
		ft_putchar_fd(n % 10 + 48, fd);
	}
}
