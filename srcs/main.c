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

int casualties = 0;

long get_time(void)
{
	static long start_time = 0;
	long actual_time;
	struct timeval tv;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		actual_time = 0;
	}
	else
	{
		gettimeofday(&tv, NULL);
		actual_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start_time;
	}
	return (actual_time);
}

int philo_death(t_data *data)
{
	if (get_time() - data->last_meal > data->params->time_to_eat)
		return (1);
	return (0);
}

void philo_sleep(t_data *data)
{
	pthread_mutex_lock(data->printf_lock);
	printf("%lu %lu is sleeping\n", get_time(), data->id);
	usleep(data->params->time_to_sleep * 1000);
	pthread_mutex_unlock(data->printf_lock);
}

void philo_eat(t_data *data)
{
	pthread_mutex_lock(&data->fork);
	pthread_mutex_lock(data->friend_fork);
	pthread_mutex_lock(data->printf_lock);
	printf("%lu %lu has taken a fork\n", get_time(), data->id);
	printf("%lu %lu is eating\n", get_time(), data->id);
	pthread_mutex_unlock(data->printf_lock);
	usleep(data->params->time_to_eat * 1000);
	data->last_meal = get_time();
	pthread_mutex_unlock(&data->fork);
	pthread_mutex_unlock(data->friend_fork);
}

void philo_think(t_data *data)
{
	pthread_mutex_lock(data->printf_lock);
	printf("%lu %lu is thinking\n", get_time(), data->id);
	pthread_mutex_unlock(data->printf_lock);
}

void *do_philo(t_data *data)
{
	while (1)
	{
		if (philo_death(data) == 1 || casualties == 1)
		{
			data->params->casualties = 1;
			printf("%lu %lu has died\n", get_time(), data->id);
			break;
		}
		philo_eat(data);
		if (philo_death(data) == 1 || casualties == 1)
		{
			data->params->casualties = 1;
			printf("%lu %lu has died\n", get_time(), data->id);
			break;
		}
		philo_sleep(data);
		if (philo_death(data) == 1 || casualties == 1)
		{
			data->params->casualties = 1;
			printf("%lu %lu has died\n", get_time(), data->id);
			break;
		}
		philo_think(data);
		if (philo_death(data) == 1 || casualties == 1)
		{
			data->params->casualties = 1;
			printf("%lu %lu has died\n", get_time(), data->id);
			break;
		}
	}
	return (NULL);
}

void philo(t_params *params)
{
	int i;
	t_data *data;
	pthread_mutex_t printf_lock;

	data = malloc(sizeof(t_data) * params->nb_of_philos);
	pthread_mutex_init(&printf_lock, NULL);
	i = 0;
	while (i < params->nb_of_philos)
	{
		data[i].id = i;
		data[i].params = params;
		data[i].printf_lock = &printf_lock;
		pthread_mutex_init(&data[i].fork, NULL);
		data[(i + 1) % params->nb_of_philos].friend_fork = &data[i].fork;
		i++;
	}
	i = 0;
	while (i < params->nb_of_philos)
	{
		pthread_create(&(data[i].philo), NULL, (void *(*)(void *)) do_philo, (void *) &data[i]);
		i++;
	}
	i = 0;
	while (i < params->nb_of_philos)
	{
		pthread_join(data[i].philo, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	int i;
	t_params params;

	i = 0;
	if (parse_input(ac, av, &params) == 1)
		return (1);
	params.casualties = 0;
	get_time();
	philo(&params);
	return (0);
}
