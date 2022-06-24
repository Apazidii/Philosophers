#include "philo.h"

t_man	*ft_create_table(long int name, t_data *data)
{
	t_man	*new;

	new = (t_man *)malloc(sizeof(t_man));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->data = data;
	new->number_eat = 0;
	new->already_eaten = 0;
	new->full = 0;
	new->checked = 0;
	return (new);
}

void	init_sem_error(sem_t *sem)
{
	sem_close(sem);
	write(1, "Sem error\n", 10);
	exit(1);
}

void	init_sems(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("philo_dead");
	sem_unlink("print");
	data->fork = sem_open("forks", O_CREAT, 0700, data->number_of_philosophers);
	if (data->fork == SEM_FAILED)
		init_sem_error(data->fork);
	data->dead_sem = sem_open("philo_dead", O_CREAT, 0700, 1);
	if (data->dead_sem == SEM_FAILED)
		init_sem_error(data->dead_sem);
	data->print = sem_open("print", O_CREAT, 0700, 1);
	if (data->print == SEM_FAILED)
		init_sem_error(data->print);
}

void	close_sem(t_data *data)
{
	if (data->fork)
	{
		sem_close(data->fork);
		sem_unlink("forks");
	}
	if (data->dead_sem)
	{
		sem_close(data->dead_sem);
		sem_unlink("philo_dead");
	}
	if (data->print)
	{
		sem_close(data->print);
		sem_unlink("print");
	}
}