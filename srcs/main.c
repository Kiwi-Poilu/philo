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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (1);
}

int	parse_input(int ac, char **av)
{
	if (ac < 6 || ac > 7)
		return (ft_putstr("Invalid number of arguments\n"));
	return (0);
}

int	main(int ac, char **av)
{
	if (parse_input(ac, av) == 1)
		return (1);
	return (0);
}
