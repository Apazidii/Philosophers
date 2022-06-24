#include "philo.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int print_error(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

int is_digits(char *s)
{
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int print_action(t_man *man, char *action)
{
	sem_wait(man->data->print);
	if (man->data->philo_dead)
	{
		sem_post(man->data->print);
		return (0);
	}
	if (timer_get_time(&man->data->timer))
	{
		man->data->error = 2;
		sem_post(man->data->print);
		return (1);
	}
	ft_putnbr_fd(man->data->timer.get_all_usec, 1);
	write(1, " ", 1);
	ft_putnbr_fd(man->name, 1);
	write(1, " ", 1);
	write(1, action, ft_strlen(action));
	sem_post(man->data->print);
	return (0);
}

int dead_print_action(t_man *man, char *action)
{
	sem_wait(man->data->print);
	if (man->data->philo_dead)
	{
		sem_post(man->data->print);
		return (0);
	}
	if (timer_get_time(&man->data->timer))
	{
		man->data->error = 2;
		sem_post(man->data->print);
		return (1);
	}
	ft_putnbr_fd(man->data->timer.get_all_usec, 1);
	write(1, " ", 1);
	ft_putnbr_fd(man->name, 1);
	write(1, " ", 1);
	write(1, action, ft_strlen(action));
	return (0);
}