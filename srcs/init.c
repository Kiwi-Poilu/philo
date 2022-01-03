/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:11:50 by kiwi              #+#    #+#             */
/*   Updated: 2022/01/02 16:11:51 by kiwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_philos(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->params->nb_of_philos)
	{
		pthread_create(&(data[i].philo), NULL,
			(void *(*)(void *))do_philo, (void *)&data[i]);
		i++;
	}
	get_time();
	pthread_mutex_unlock(data->printf_lock);
	i = 0;
	while (i < data->params->nb_of_philos)
	{
		pthread_mutex_unlock(&data[i].self_lock);
		i += 2;
	}
	usleep(data->params->time_to_eat / 2 * 1000);
	i = 1;
	while (i < data->params->nb_of_philos)
	{
		pthread_mutex_unlock(&data[i].self_lock);
		i += 2;
	}
}

void	create_philos(t_data *data, pthread_mutex_t printf_lock,
			t_params *params)
{
	size_t				i;
	pthread_mutexattr_t	mode;

	i = 0;
	mode = (pthread_mutexattr_t)PTHREAD_MUTEX_ERRORCHECK;
	while (i != params->nb_of_philos)
	{
		pthread_mutex_init(&data[i].self_lock, NULL);
		pthread_mutex_lock(&data[i].self_lock);
		data[i].id = i + 1;
		data[i].meal = 0;
		data[i].last_meal = 0;
		data[i].params = params;
		data[i].printf_lock = &printf_lock;
		pthread_mutex_init(&data[i].right_fork, &mode);
		data[(i + 1) % params->nb_of_philos].left_fork = &data[i].right_fork;
		i++;
	}
}
