#ifndef PHILO_PHILO_H
# define PHILO_PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_params
{
	int nb_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_of_meals;
	int casualties;
	int enough_meals;
}				t_params;

typedef struct	s_data
{
	size_t id;
	long last_meal;
	int meal;
	t_params *params;
	pthread_t philo;
	pthread_mutex_t self_lock;
	pthread_mutex_t right_fork;
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*printf_lock;
}				t_data;

//main.c
int ft_putstr(char *str);

//parsing.c
int	is_number(const char *nb);
int check_if_nb(int ac, char **av);
int	parse_input(int ac, char **av, t_params *params);

//ft_strtol.c
int	ft_strtol(const char *nptr);

//utils.c
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isspace(int c);
int	ft_isupper(int c);
long get_time(void);

//utils.c
int	ft_putstr(char *str);

#endif
