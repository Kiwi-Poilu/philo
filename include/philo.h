#ifndef PHILO_PHILO_H
# define PHILO_PHILO_H

# include <stdio.h>
# include <unistd.h>

typedef struct s_params
{
	int nb_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_of_meals;
}				t_params;

#endif
