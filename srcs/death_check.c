/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:12:08 by kiwi              #+#    #+#             */
/*   Updated: 2022/01/02 16:12:09 by kiwi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_kill(t_data *data)
{
	pthread_mutex_lock(data->printf_lock);
	if (data->params->casualties != 1 && data->params->enough_meals
		!= (ssize_t)data->params->nb_of_philos)
		printf("%lu %zu has died\n", get_time(), data->id);
	data->params->casualties = 1;
	pthread_mutex_unlock(data->printf_lock);
}

int	checker_loop(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->params->nb_of_philos)
	{
		pthread_mutex_lock(data[i].printf_lock);
		if (data->params->casualties != 0)
		{
			pthread_mutex_unlock(data[i].printf_lock);
			return (1);
		}
		pthread_mutex_unlock(data[i].printf_lock);
		pthread_mutex_lock(&data[i].self_lock);
		if ((get_time() - data[i].last_meal) >= data->params->time_to_die)
		{
			pthread_mutex_unlock(&data[i].self_lock);
			philo_kill(&data[i]);
			return (1);
		}
		pthread_mutex_unlock(&data[i].self_lock);
		i++;
	}
	return (0);
}

void	*check_death(void *tmp)
{
	size_t	prev;
	size_t	now;
	t_data	*data;

	data = (t_data *)tmp;
	pthread_mutex_lock(data->printf_lock);
	pthread_mutex_unlock(data->printf_lock);
	while (1)
	{
		prev = get_time();
		if (checker_loop(data) == 1)
			return (NULL);
		now = get_time();
		if (now - prev < 4)
			usleep((4 - (prev - now)) * 1000);
	}
}
