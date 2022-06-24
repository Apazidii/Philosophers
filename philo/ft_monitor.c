#include "philo.h"

void *philo_monitor(void *arg)
{
	t_man		*man;
	t_data		*data;
	long int	philo_full;

	man = (t_man *)arg;
	data = man->data;
	philo_full = 0;
	while (data->philo_dead == 0 && data->error == 0)
	{
		if (timer_get_time(&man->man_timer) != 0)
			data->error = 3;
		if (man->man_timer.get_all_usec >= man->data->time_to_die)
		{
			print_action(man, "died\n");
			man->data->philo_dead = 1;
		}
//		pthread_mutex_lock(&man->data->terminal_mutex);
//		ft_putnbr_fd(man->number_eat, 1);
//		write(1, "\n", 1);
//		pthread_mutex_unlock(&man->data->terminal_mutex);
		if (man->checked == 0)
		{
			if (man->number_eat >= data->number_of_times_each_philosopher_must_eat)
			{
				philo_full++;
				man->checked = 1;
			}
		}
		if (philo_full == data->number_of_philosophers)
			man->data->philo_dead = 1;
		man = man->left_man;
	}
}
