#include "philo.h"




void philo_eating(t_man *man)
{
	if (man->use_left_fork == 1 && man->use_right_fork == 1)
	{
		print_action(man, "is eating\n");
		if (man->number_eat > 8)
			printf("a");
		timer_start(&man->man_timer);
		usleep(man->data->time_to_eat * 1000);
		pthread_mutex_lock(&man->left_fork->mutex);
		man->use_left_fork = 0;
		man->left_fork->now_used = 0;
		pthread_mutex_unlock(&man->left_fork->mutex);
		pthread_mutex_lock(&man->right_fork->mutex);
		man->use_right_fork = 0;
		man->right_fork->now_used = 0;
		pthread_mutex_unlock(&man->right_fork->mutex);
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

void *philo_life(void *arg)
{
	t_man *man;

	man = (t_man *) arg;
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

