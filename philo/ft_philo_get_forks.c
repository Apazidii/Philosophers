#include "philo.h"


void philo_get_fork(t_man *man, int k)
{
	t_fork *fork;

	if (k == 1)
		fork = man->left_fork;
	else if (k == 0)
		fork = man->right_fork;
	pthread_mutex_lock(&fork->mutex);
	if (fork->now_used == 0)
	{
		fork->now_used = 1;
		if (k == 1)
			man->use_left_fork = 1;
		else if (k == 0)
			man->use_right_fork = 1;
		print_action(man, "has taken a fork\n");
		man->thinking_now = 0;
		philo_thinking(man);
	}
	pthread_mutex_unlock(&fork->mutex);
}

void philo_get_forks(t_man *man)
{
	while ((man->use_right_fork != 1 || man->use_left_fork != 1) && man->data->philo_dead == 0)
	{
		if (man->use_right_fork == 0)
			philo_get_fork(man, 0);
		if (man->use_left_fork == 0)
			philo_get_fork(man, 1);
		philo_thinking(man);
	}
}
