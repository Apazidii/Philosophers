#include "philo.h"


int atoi_long(char *s, long int *res)
{
	long int b;

	*res = 0;
	if (!is_digits(s) || ft_strlen(s) > 20)
		return (1);
	b = 0;
	while (*s != '\0')
	{
		b = b * 10 + (*s - '0');
		s++;
	}
	if (b < 0)
		return (1);
	*res = b;
	return (0);
}