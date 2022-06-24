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
	return (0);
}


void add_all_philo(t_man *table, t_data *data, long int num)
{
	long int i;

	i = 2;
	while (i <= num)
	{
		if (!ft_add_new_philo(&table, data, i))
		{
			ft_free_list(table, num);
			print_error("Error malloc\n");
			exit(1);
		}

		i++;
	}
}

void add_forks(t_man *table, long int n)
{
	long int i;

	i = n;
	while (i--)
	{
		if (!create_fork(table))
		{
			ft_free_list(table, n);
			print_error("Error malloc\n");
			exit(1);
		}
		table = table->left_man;
	}
}

void print_table(t_man *man, long int n)
{
	if (n == 0)
		return;
	printf("my name  %ld %10s\n", man->name, " ");
	printf("my left  %ld %10s left fork  %d\n", man->left_man->name, " ", man->left_fork->now_used);
	printf("my right %ld %10s right fork %d\n", man->right_man->name, " ", man->right_fork->now_used);
	printf("---------------------------\n");
	print_table(man->left_man, n -1);
}

void start_lunch(t_man *table, t_data *data)
{
	long int i;

	i = data->number_of_philosophers;
	if (pthread_mutex_init(&(data->terminal_mutex), NULL))
	{
		data->error = 1;
		return ;
	}
	if (timer_start(&data->timer) != 0)
	{
		data->error = 1;
		return ;
	}
	while (i--)
	{
		if (pthread_create(&(table->p), NULL, philo_life, (void *) table))
		{
			data->error = 1;
			return;
		}
		table = table->left_man;
	}
	pthread_create(&data->p_monitor, NULL, philo_monitor, (void *) table);
	pthread_join(data->p_monitor, NULL);
	i = data->number_of_philosophers;
	while (i--)
	{
		pthread_join(table->p, NULL);
//		printf("%ld end\n", table->name);
		table = table->left_man;
	}
}


int main(int argc, char *argv[])
{
	t_data data;
	t_man *table;

	if (argc != 5 && argc != 6)
		return print_error("Invalid number of arguments\n");
	if (init(argc, argv, &data))
		return print_error("Invalid arguments\n");
	table = ft_create_table(1, &data);
	if (!table)
		return print_error("Error malloc\n");
	add_all_philo(table, &data, data.number_of_philosophers);
	add_forks(table, data.number_of_philosophers);
	start_lunch(table, &data);
	if (data.error == 1)
		print_error("Error\n");
	ft_free_list(table, data.number_of_philosophers);
}