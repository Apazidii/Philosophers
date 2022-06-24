#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>


#include <string.h>


typedef struct s_timer
{
	double time;


	long int get_all_usec;
}	t_timer;


typedef struct s_data
{
	t_timer 		timer;
	pthread_mutex_t terminal_mutex;
	pthread_t		p_monitor;

	int				error;
	int				philo_dead;

	long int		number_of_philosophers;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		number_of_times_each_philosopher_must_eat;
}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				now_used;
}	t_fork;

typedef struct s_man
{
	pthread_t		p;
	t_data			*data;
	t_timer			man_timer;

	struct s_man	*left_man;
	struct s_man	*right_man;

	t_fork			*left_fork;
	t_fork			*right_fork;

	long int		name;

	int				use_left_fork;
	int				use_right_fork;

	int				already_eaten;
	int 			thinking_now;
	long int		number_eat;

	int 			full;
	int 			checked;

}	t_man;



//philo action
void *philo_life(void *arg);
void philo_thinking(t_man *man);

//forks
void philo_get_forks(t_man *man);

//math utils
int atoi_long(char *s, long int *res);


//list utils
t_man	*ft_create_table(long int name, t_data *data);
t_man	*ft_add_new_philo(t_man **table, t_data *data, long int name);
void	ft_free_list(t_man *table, long int n);
t_fork	*create_fork(t_man *man);

//str utils
int ft_strlen(char *s);
int print_error(char *s);
int is_digits(char *s);
int print_action(t_man *man, char *action);

//monitor
void *philo_monitor(void *arg);


//timer
int timer_start(t_timer *t);
int timer_get_time(t_timer *t);
void timer_restart(t_timer *t);

//lib
void	ft_putnbr_fd(long int n, int fd);

#endif