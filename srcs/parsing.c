/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 14:46:13 by kiwi              #+#    #+#             */
/*   Updated: 2022/01/02 14:46:15 by kiwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_number(const char *nb)
{
	int	i;

	i = 0;
	if (nb[i] == '-')
		return (1);
	while (nb[i])
	{
		if (nb[i] < '0' || nb[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_if_nb(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int	fill_params(int ac, char **av, t_params *params)
{
	params->nb_of_philos = ft_strtol(av[1]);
	if (params->nb_of_philos == 0)
		return (printf("There must be at least one philosopher\n"));
	params->time_to_die = ft_strtol(av[2]);
	params->time_to_eat = ft_strtol(av[3]);
	params->time_to_sleep = ft_strtol(av[4]);
	if (ac == 6)
	{
		params->nb_of_meals = ft_strtol(av[5]);
		if (params->nb_of_meals == 0)
			return (1);
	}
	else
		params->nb_of_meals = -1;
	if (errno == ERANGE)
		return (printf("Some of the arguments exceed the limits of integers\n"));
	return (0);
}

int	parse_input(int ac, char **av, t_params *params)
{
	if (ac < 5 || ac > 6)
		return (printf("Invalid number of arguments\n"));
	if (check_if_nb(ac, av) == 1)
	{
		printf("Some of the arguments are not valid positive numbers\n");
		return (1);
	}
	if (fill_params(ac, av, params) != 0)
		return (1);
	return (0);
}
