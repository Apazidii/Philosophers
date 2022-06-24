#include "philo.h"

t_man	*ft_create_table(long int name, t_data *data)
{
	t_man	*new;

	new = (t_man *)malloc(sizeof(t_man));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->data = data;
	new->number_eat = 0;
	new->already_eaten = 0;
	new->full = 0;
	new->checked = 0;
	new->left_man = new;
	new->right_man = new;
	new->left_fork = NULL;
	new->right_fork = NULL;
	return (new);
}

t_man	*ft_add_new_philo(t_man **table, t_data *data, long int name)
{
	t_man	*new;

	new = (t_man *)malloc(sizeof(t_man));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->use_right_fork = 0;
	new->use_left_fork = 0;
	new->data = data;
	new->number_eat = 0;
	new->full = 0;
	new->checked = 0;
	new->already_eaten = 0;
	new->thinking_now = 0;
	new->left_man = (*table);
	new->right_man = (*table)->right_man;
	(*table)->right_man->left_man = new;
	(*table)->right_man = new;
	new->left_fork = NULL;
	new->right_fork = NULL;
	return (new);
}

void ft_free_list(t_man *table, long int n)
{
	t_man *next;

	if (!table)
		return;
	while (n--)
	{
		if (table)
		{
			if (table->left_fork)
				pthread_mutex_destroy(&(table->left_fork->mutex));
			if (table->left_fork)
				free(table->left_fork);
			next = table->right_man;
			free(table);
			table = next;
		}
	}
}

t_fork *create_fork(t_man *man)
{
	t_fork *f;

	f = (t_fork *)malloc(sizeof(t_fork));
	if (!f)
		return (NULL);
	if (pthread_mutex_init(&(f->mutex), NULL))
	{
		free(f);
		return (NULL);
	}
	man->left_fork = f;
	man->left_man->right_fork = f;
	f->now_used = 0;
	return (f);
}