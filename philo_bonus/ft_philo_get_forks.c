#include "philo.h"


void philo_get_forks(t_man *man)
{
		sem_wait(man->data->fork);
		man->use_forks++;
		print_action(man, "has taken a fork\n");
		man->thinking_now = 0;
		philo_thinking(man);
		sem_wait(man->data->fork);
		man->use_forks++;
		print_action(man, "has taken a fork\n");
		man->thinking_now = 0;
		philo_thinking(man);
}
