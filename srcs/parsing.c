#include "../include/philo.h"

int	is_number(const char *nb)
{
	int	i;

	i = 0;
	if (nb[i] == '-')
		i++;
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int check_if_nb(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (is_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int fill_params(int ac, char **av, t_params *params)
{
	params->nb_of_philos = ft_strtol(av[1]);
	params->time_to_die = ft_strtol(av[2]);
	params->time_to_eat = ft_strtol(av[3]);
	params->time_to_sleep = ft_strtol(av[4]);
	if (ac == 6)
		params->nb_of_meals = ft_strtol(av[5]);
	else (params->nb_of_meals = -1);
	if (errno == ERANGE)
		return (1);
	return (0);
}

int	parse_input(int ac, char **av, t_params *params)
{
	if (ac < 5 || ac > 6)
		return (printf("Invalid number of arguments\n"));
	if (check_if_nb(ac, av) == 1)
		return (printf("Some of the arguments are not numbers\n"));
	if (fill_params(ac, av, params) == 1)
		return (printf("Some of the arguments exceed the limits of integers\n"));
	return (0);
}