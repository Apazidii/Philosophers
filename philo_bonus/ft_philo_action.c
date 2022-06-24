#include "philo.h"


void new_man(t_data *data, int name)
{
	t_man man;

	man.name = name;
	man.data = data;
	man.number_eat = 0;
	man.already_eaten = 0;
	man.full = 0;
	man.use_forks = 0;
	man.checked = 0;
	pthread_create(&man.dead_monitor, NULL, dead_monitor, (void *) &man);
	pthread_create(&man.stop_monitor, NULL, stop_monitor, (void *) &man);
	philo_life(&man);
	pthread_join(man.dead_monitor, NULL);
	pthread_join(man.stop_monitor, NULL);
}

void philo_eating(t_man *man)
{
	if (man->use_forks == 2)
	{
		print_action(man, "is eating\n");
		if (man->number_eat > 8)
			printf("a");
		timer_start(&man->man_timer);
		usleep(man->data->time_to_eat * 1000);
		sem_post(man->data->fork);
		sem_post(man->data->fork);
		man->already_eaten = 1;
		man->thinking_now = 0;
		man->number_eat++;
	}
}

void philo_sleeping(t_man *man)
{
	if (man->already_eaten == 1)
	{
		print_action(man, "is sleeping\n");
		man->thinking_now = 0;
		man->already_eaten = 0;
		usleep(man->data->time_to_sleep * 1000);
	}
}

void philo_thinking(t_man *man)
{
	if (man->thinking_now == 0)
	{
		man->thinking_now = 1;
		print_action(man, "is thinking\n");
	}
}

void *philo_life(t_man *man)
{
	while (man->data->error == 0 && man->data->philo_dead == 0)
	{
		if (timer_start(&man->man_timer) != 0)
		{
			man->data->error = 3;
			return NULL;
		}
		philo_get_forks(man);
		philo_eating(man);
		philo_sleeping(man);
		philo_thinking(man);
	}
}

