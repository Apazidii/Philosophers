#include "philo.h"

void *dead_monitor(void *arg)
{
	t_man		*man;
	t_data		*data;

	man = (t_man *)arg;
	data = man->data;
	while (data->philo_dead == 0 && data->error == 0)
	{
		if (timer_get_time(&man->man_timer) != 0)
			data->error = 3;
		if (man->man_timer.get_all_usec >= man->data->time_to_die)
		{
			dead_print_action(man, "died\n");
			man->data->philo_dead = 1;
		}
	}
	return (NULL);
}

void *stop_monitor(void *arg)
{
	t_man		*man;
	t_data		*data;


	return (NULL);
}
