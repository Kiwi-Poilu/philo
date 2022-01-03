/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:11:43 by kiwi              #+#    #+#             */
/*   Updated: 2022/01/02 16:11:43 by kiwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_sleep(t_data *data)
{
	printf_locked(data, "is sleeping", NULL);
	usleep(data->params->time_to_sleep * 1000);
}

int	philo_take_fork(t_data *data)
{
	if (data->id % 2 == 0)
		pthread_mutex_lock(&data->right_fork);
	else
		pthread_mutex_lock(data->left_fork);
	printf_locked(data, "has taken a fork", NULL);
	if (data->id % 2 == 0)
	{
		if (pthread_mutex_lock(data->left_fork))
		{
			pthread_mutex_unlock(&data->right_fork);
			return (1);
		}
	}
	else
	{
		if (pthread_mutex_lock(&data->right_fork))
		{
			pthread_mutex_unlock(data->left_fork);
			return (1);
		}
	}
	return (0);
}

int	philo_eat(t_data *data)
{
	if (philo_take_fork(data) == 1)
		return (1);
	pthread_mutex_lock(&data->self_lock);
	if ((get_time() - data->last_meal) >= data->params->time_to_die)
		philo_kill(data);
	pthread_mutex_unlock(&data->self_lock);
	printf_locked(data, "has taken a fork", "is eating");
	pthread_mutex_lock(&data->self_lock);
	data->last_meal = get_time();
	data->meal++;
	pthread_mutex_unlock(&data->self_lock);
	usleep(data->params->time_to_eat * 1000);
	pthread_mutex_unlock(&data->right_fork);
	pthread_mutex_unlock(data->left_fork);
	return (0);
}

void	philo_think(t_data *data)
{
	pthread_mutex_lock(data->printf_lock);
	printf("%lu %lu is thinking\n", get_time(), data->id);
	pthread_mutex_unlock(data->printf_lock);
}
