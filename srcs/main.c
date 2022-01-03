/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:32:02 by sobouatt          #+#    #+#             */
/*   Updated: 2021/11/27 18:32:03 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printf_locked(t_data *data, const char *msg1, char *msg2)
{
	pthread_mutex_lock(data->printf_lock);
	if (data->params->casualties != 1)
	{
		printf("%lu %lu %s\n", get_time(), data->id, msg1);
		if (msg2 != NULL)
			printf("%lu %lu %s\n", get_time(), data->id, msg2);
	}
	pthread_mutex_unlock(data->printf_lock);
}

void	do_philo2(t_data *data)
{
	pthread_mutex_lock(data->printf_lock);
	if (data->meal == data->params->nb_of_meals)
		data->params->enough_meals++;
	pthread_mutex_unlock(data->printf_lock);
	if (data->params->nb_of_philos == data->id
		&& data->params->nb_of_philos % 2 == 1)
		usleep(data->params->time_to_sleep * 333);
	philo_sleep(data);
	printf_locked(data, "is thinking", NULL);
	pthread_mutex_lock(data->printf_lock);
}

void	*do_philo(t_data *data)
{
	pthread_mutex_lock(&data->self_lock);
	pthread_mutex_unlock(&data->self_lock);
	while (1)
	{
		pthread_mutex_lock(data->printf_lock);
		if (data->params->casualties != 0)
		{
			pthread_mutex_unlock(data->printf_lock);
			break ;
		}
		pthread_mutex_unlock(data->printf_lock);
		if (philo_eat(data) == 1)
			return (NULL);
		do_philo2(data);
		if (data->params->enough_meals >= (ssize_t)data->params->nb_of_philos)
		{
			data->params->casualties = 1;
			pthread_mutex_unlock(data->printf_lock);
			break ;
		}
		pthread_mutex_unlock(data->printf_lock);
	}
	return (NULL);
}

void	philo(t_params *params)
{
	t_data				*data;
	pthread_mutex_t		printf_lock;
	pthread_t			watcher;
	size_t				i;

	params->casualties = 0;
	params->enough_meals = 0;
	data = malloc(sizeof(t_data) * params->nb_of_philos);
	pthread_mutex_init(&printf_lock, NULL);
	create_philos(data, printf_lock, params);
	pthread_mutex_lock(data->printf_lock);
	pthread_create(&watcher, NULL, (void *)check_death, (void *)data);
	start_philos(data);
	i = 0;
	while (i < params->nb_of_philos)
	{
		pthread_join(data[i].philo, NULL);
		i++;
	}
	pthread_join(watcher, NULL);
	free(data);
}

int	main(int ac, char **av)
{
	t_params	params;

	if (ac < 5 || ac > 6)
		return (printf("Invalid number of arguments\n"));
	if (parse_input(ac, av, &params) != 0)
		return (1);
	philo(&params);
	return (0);
}
