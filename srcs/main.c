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

void philo_kill(t_data *data)
{
	pthread_mutex_lock(data->printf_lock);
	if (data->params->casualties != 1 && data->params->enough_meals != data->params->nb_of_philos)
		printf("%lu %zu has died\n",  get_time(), data->id);
	data->params->casualties = 1;
	pthread_mutex_unlock(data->printf_lock);
}

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

void	*check_death(void *tmp)
{
	int i;

	t_data *data = (t_data *)tmp;
	pthread_mutex_lock(data->printf_lock);
	pthread_mutex_unlock(data->printf_lock);
	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->params->nb_of_philos)
		{
			pthread_mutex_lock(data[i].printf_lock);
			if (data->params->casualties != 0 )
			{
				pthread_mutex_unlock(data[i].printf_lock);
				return (NULL);
			}
			pthread_mutex_unlock(data[i].printf_lock);
			pthread_mutex_lock(&data[i].self_lock);
			if ((get_time() - data[i].last_meal) >= data->params->time_to_die)
			{
				pthread_mutex_unlock(&data[i].self_lock);
				philo_kill(&data[i]);
				return (NULL);
			}
			pthread_mutex_unlock(&data[i].self_lock);
			i++;
		}
	}
}


void philo_sleep(t_data *data)
{
		printf_locked(data, "is sleeping", NULL);
		usleep(data->params->time_to_sleep * 1000);
}

void philo_eat(t_data *data)
{
	if (data->id % 2 == 1)
		pthread_mutex_lock(&data->right_fork);
	else
		pthread_mutex_lock(data->left_fork);
	printf_locked(data, "has taken a fork", NULL);
	if (data->id % 2 == 1)
		pthread_mutex_lock(data->left_fork);
	else
		pthread_mutex_lock(&data->right_fork);
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
}

void philo_think(t_data *data)
{
	pthread_mutex_lock(data->printf_lock);
	printf("%lu %lu is thinking\n", get_time(), data->id);
	pthread_mutex_unlock(data->printf_lock);
}

void *do_philo(t_data *data)
{
	pthread_mutex_lock(&data->self_lock);
	pthread_mutex_unlock(&data->self_lock);
	while (1)
	{
		pthread_mutex_lock(data->printf_lock);
		if (data->params->casualties != 0)
		{
			pthread_mutex_unlock(data->printf_lock);
			break;
		}
		pthread_mutex_unlock(data->printf_lock);
		philo_eat(data);
		pthread_mutex_lock(data->printf_lock);
		if (data->meal == data->params->nb_of_meals)
			data->params->enough_meals++;
		pthread_mutex_unlock(data->printf_lock);
		philo_sleep(data);
		printf_locked(data, "is thinking", NULL);
		pthread_mutex_lock(data->printf_lock);
		if (data->params->enough_meals >= data->params->nb_of_philos)
		{
			data->params->casualties = 1;
			pthread_mutex_unlock(data->printf_lock);
			break;
		}
		pthread_mutex_unlock(data->printf_lock);
	}
	return (NULL);
}

void philo(t_params *params)
{
	int i;
	t_data *data;
	pthread_mutex_t printf_lock;
	pthread_t watcher;

	params->casualties = 0;
	params->enough_meals = 0;
	data = malloc(sizeof(t_data) * params->nb_of_philos);
	pthread_mutex_init(&printf_lock, NULL);
	pthread_mutex_lock(&printf_lock);
	i = 0;
	while (i != params->nb_of_philos)
	{
		pthread_mutex_init(&data[i].self_lock, NULL);
		pthread_mutex_lock(&data[i].self_lock);
		data[i].id = i + 1;
		data[i].meal = 0;
		data[i].last_meal = 0;
		data[i].params = params;
		data[i].printf_lock = &printf_lock;
		pthread_mutex_init(&data[i].right_fork, NULL);
		data[(i + 1) % params->nb_of_philos].left_fork = &data[i].right_fork;
		i++;
	}
	pthread_create(&watcher, NULL, (void *)check_death, (void *)data);
	i = 0;
	while (i < params->nb_of_philos)
	{
		pthread_create(&(data[i].philo), NULL, (void *(*)(void *)) do_philo, (void *) &data[i]);
		i++;
	}
	get_time();
	pthread_mutex_unlock(&printf_lock);
	i = 0;
	while (i < params->nb_of_philos)
	{
		pthread_mutex_unlock(&data[i].self_lock);
		i+=2;
	}
	usleep(params->time_to_eat / 2 * 1000);
	i = 1;
	while (i < params->nb_of_philos)
	{
		pthread_mutex_unlock(&data[i].self_lock);
		i+=2;
	}
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
	int i;
	t_params params;

	i = 0;
	if (parse_input(ac, av, &params) != 0)
		return (1);
	philo(&params);
	return (0);
}
