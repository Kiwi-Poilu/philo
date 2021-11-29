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

void create_list(t_params *params)
{
	int i;

	i = 0;
	while (i < params->nb_of_philos)
	{
		pthread_create()
	}
}

int	main(int ac, char **av)
{
	int i;
	t_params params;

	i = 0;
	if (parse_input(ac, av, &params) == 1)
		return (1);
	create_list(&params);
	get_time();
	return (0);
}
