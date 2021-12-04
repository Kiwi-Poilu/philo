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

void push(t_node **head, void *new_content)
{
	t_node *new_node;

	//allocate
	new_node = (t_node*)malloc(sizeof(t_node));
	//put in the content
	new_node->content = new_content;
	//self explanatory
	new_node->next = (*head);
	new_node->prev = NULL;
	//on deplace
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void *do_philo(void *params)
{
	t_params *args = (t_params *)params;
	printf("Philo is sleeping\n");
	usleep(args->time_to_sleep * 1000);
	printf("Philo is eating\n");
	usleep(args->time_to_eat * 1000);
	printf("Philo is dying\n");
	usleep(args->time_to_eat * 1000);
	return (NULL);
}

void philo(t_params *params)
{
	int i;
	pthread_t *thread;

	i = 0;
	thread = malloc(sizeof(pthread_t) * params->nb_of_philos);
	if (thread == NULL)
		ft_putstr("Error could not malloc nb_of_philos threads\n");
	while (i < params->nb_of_philos)
	{
		pthread_create(&thread[i], NULL, do_philo, (void *) params);
		i++;
	}
	i = 0;
	while (i < params->nb_of_philos)
	{
		pthread_join(thread[i], NULL);
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
