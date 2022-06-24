#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct s_timer
{
	double time;


	long int get_all_usec;
}	t_timer;


typedef struct s_data
{
	t_timer 		timer;
	pthread_mutex_t terminal_mutex;
	int				*pids;

	sem_t			*fork;
	sem_t			*print;
	sem_t			*dead_sem;

	int				error;
	int				philo_dead;

	long int		number_of_philosophers;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		number_of_times_each_philosopher_must_eat;
}	t_data;

typedef struct s_man
{
	pthread_t		dead_monitor;
	pthread_t		stop_monitor;
	t_data			*data;
	t_timer			man_timer;

	int 			use_forks;

	long int		name;

	int				already_eaten;
	int 			thinking_now;
	long int		number_eat;

	int 			full;
	int 			checked;

}	t_man;



//philo action
void *philo_life(t_man *man);
void philo_thinking(t_man *man);

//forks
void philo_get_forks(t_man *man);

//math utils
int atoi_long(char *s, long int *res);


//list utils
void	ft_free_list(t_man *table, long int n);
void	init_sems(t_data *data);
void	close_sem(t_data *data);


//str utils
int ft_strlen(char *s);
int print_error(char *s);
int is_digits(char *s);
int print_action(t_man *man, char *action);
int dead_print_action(t_man *man, char *action);

//monitor
void *dead_monitor(void *arg);
void *stop_monitor(void *arg);
void new_man(t_data *data, int name);

//timer
int timer_start(t_timer *t);
int timer_get_time(t_timer *t);
void timer_restart(t_timer *t);

//lib
void	ft_putnbr_fd(long int n, int fd);

#endif