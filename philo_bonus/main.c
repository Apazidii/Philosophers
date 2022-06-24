#include "philo.h"



//error code:
//2 = error print
//3 = error timer


int init(int argc, char **argv, t_data *data)
{
	long int res;

	if (atoi_long(argv[1], &res))
		return (1);
	data->number_of_philosophers = res;
	if (atoi_long(argv[2], &res))
		return (1);
	data->time_to_die = res;
	if (atoi_long(argv[3], &res))
		return (1);
	data->time_to_eat = res;
	if (atoi_long(argv[4], &res))
		return (1);
	data->time_to_sleep = res;
	if (argc == 6)
	{
		if (atoi_long(argv[5], &res))
			return (1);
		data->number_of_times_each_philosopher_must_eat = res;
	}
	else
		data->number_of_times_each_philosopher_must_eat = LONG_MAX;
	data->error = 0;
	data->philo_dead = 0;
	data->pids = (int *)malloc(sizeof(int *) * data->number_of_philosophers);
	if (data->pids == NULL)
	{
		write(1, "Malloc error\n", 13);
		exit(1);
	}
	return (0);
}

void	kills(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		kill(data->pids[i], SIGINT);
		i++;
	}
}

void start_lunch(t_data *data)
{
	long int i;

	i = 0;
	timer_start(&data->timer);
	while (i < data->number_of_philosophers)
	{
		(data->pids)[i] = fork();
		if ((data->pids)[i] == 0)
			new_man(data, i + 1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		waitpid(data->pids[i], 0, 0);
		i++;
	}
	kills(data);
	close_sem(data);
	free(data->pids);

}


int main(int argc, char *argv[])
{
	t_data data;
	t_man *table;

	if (argc != 5 && argc != 6)
		return print_error("Invalid number of arguments\n");
	if (init(argc, argv, &data))
		return print_error("Invalid arguments\n");
	init_sems(&data);
	start_lunch(&data);
	if (data.error == 1)
		print_error("Error\n");
//	ft_free_list(table, data.number_of_philosophers);
}