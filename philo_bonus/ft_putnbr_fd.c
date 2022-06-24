#include "philo.h"

static void	func(long long int n, int fd)
{
	char	c;

	if (n >= 10)
		func(n / 10, fd);
	c = '0' + (n % 10);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long int n, int fd)
{
	long long int	num;

	num = n;
	if (num < 0)
	{
		num = num * -1;
		write(fd, "-", 1);
	}
	func(num, fd);
}
