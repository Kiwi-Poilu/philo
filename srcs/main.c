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

void	*check_death(void *tmp)
{
	
	int i;


	t_data *data = (t_data *)tmp;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->params->nb_of_philos)
		{
			if ((get_time() - data[i].last_meal) > data->params->time_to_die)
			{
				printf("%lu PHILO %zu DIED\n", get_time(), data[i].id);
				printf("%lu %lu\n", data[i].last_meal, get_time());
				exit(127);
			}
			i++;
		}
	}
	return (tmp);
}

void	printf_locked(t_data *data, const char *msg1, char *msg2)
{
	pthread_mutex_lock(data->printf_lock);
	printf("%lu %lu %s\n", get_time(), data->id, msg1);
	if (msg2 != NULL)
		printf("%lu %lu %s\n", get_time(), data->id, msg2); 
	pthread_mutex_unlock(data->printf_lock);
}

void philo_sleep(t_data *data)
{
	printf_locked(data, "is sleeping", NULL);
	usleep(data->params->time_to_sleep * 1000);
}

void philo_eat(t_data *data)
{
	if (data->id % 2 == 0)
		pthread_mutex_lock(&data->right_fork);
	else
		pthread_mutex_lock(data->left_fork);
	printf_locked(data, "has taken a fork", NULL);
	if (data->id % 2 == 0)
		pthread_mutex_lock(data->left_fork);
	else
		pthread_mutex_lock(&data->right_fork);
	printf_locked(data, "has taken a fork", "is eating");
	data->last_meal = get_time();
	usleep(data->params->time_to_eat * 1000);
	data->last_meal = get_time();
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
	while (data->meal != data->params->nb_of_meals)
	{
		philo_eat(data);
		philo_sleep(data);
		printf_locked(data, "is thinking", NULL);
		data->meal++;
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
	data = malloc(sizeof(t_data) * params->nb_of_philos);
	pthread_mutex_init(&printf_lock, NULL);
	i = 0;
	while (i != params->nb_of_philos)
	{
		data[i].id = i + 1;
		data[i].meal = 0;
		data[i].params = params;
		data[i].printf_lock = &printf_lock;
		pthread_mutex_init(&data[(i) % params->nb_of_philos].right_fork, NULL);
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
	get_time();
	philo(&params);
	return (0);
}
