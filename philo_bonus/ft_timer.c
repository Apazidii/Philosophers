#include "philo.h"


int timer_start(t_timer *t)
{
	int				f;
	struct timeval	tv;
	struct timezone	tz;
	double			sec;
	double			usec;


	f = gettimeofday(&tv, &tz);
	if (f == 0)
	{
		sec = (double) tv.tv_sec;
		usec = (double) tv.tv_usec;
		t->time = sec + (usec / 1000000);
	}
	else if (f == -1)
	{
		t->time = 0;
	}
	return (f);
}

int timer_get_time(t_timer *t)
{
	int				f;
	struct timeval	tv;
	struct timezone	tz;
	double			sec;
	double			usec;
	double			time;

	f = gettimeofday(&tv, &tz);
	if (f == 0)
	{
		sec = (double) tv.tv_sec;
		usec = (double) tv.tv_usec;
		time = sec + (usec / 1000000);
		time = time - t->time;
		time *= 1000;

		t->get_all_usec = (int) time;
	}
	else if (f == -1)
	{
		t->time = 0;
	}
	return (f);
}

//void timer_restart(t_timer *t)
//{
//	t->get_usec = 0;
//	t->get_sec = 0;
//	t->usec = 0;
//	t->sec = 0;
//	t->get_all_usec = 0;
//}

