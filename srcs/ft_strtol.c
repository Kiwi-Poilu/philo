/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <sobouatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:33:40 by sobouatt          #+#    #+#             */
/*   Updated: 2021/11/28 17:33:41 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	big_while(const char *nptr, int i[4], unsigned int ui[2])
{
	while (1)
	{
		if (ft_isdigit(i[0]))
			i[0] -= '0';
		else if (ft_isalpha(i[0]))
		{
			if (ft_isupper(i[0]))
				i[0] -= 'A' - 10;
			else
				i[0] -= 'a' - 10;
		}
		else
			break ;
		if (i[0] >= 10)
			break ;
		if (i[2] < 0 || ui[1] > ui[0] || (ui[1] == ui[0] && i[0] > i[3]))
			i[2] = -1;
		else
		{
			i[2] = 1;
			ui[1] *= 10;
			ui[1] += i[0];
		}
		i[0] = *nptr++;
	}
}

void	if_forest(const int ints[4], unsigned int u_ints[2])
{
	if (ints[2] < 0)
	{
		if (ints[1])
			u_ints[1] = INT_MIN;
		else
			u_ints[1] = INT_MAX;
		errno = ERANGE;
	}
	else if (ints[1])
		u_ints[1] = -u_ints[1];
}

int	ft_strtol(const char *nptr)
{
	int				ints[4];
	unsigned int	u_ints[2];

	ints[1] = 0;
	ints[0] = *nptr++;
	while (ft_isspace(ints[0]))
		ints[0] = *nptr++;
	if (ints[0] == '-')
	{
		ints[1] = 1;
		ints[0] = *nptr++;
	}
	else if (ints[0] == '+')
		ints[0] = *nptr++;
	if (ints[1])
		u_ints[0] = -INT_MIN;
	else
		u_ints[0] = INT_MAX;
	ints[3] = u_ints[0] % 10;
	u_ints[0] /= 10;
	u_ints[1] = 0;
	ints[2] = 0;
	big_while(nptr, ints, u_ints);
	if_forest(ints, u_ints);
	return (u_ints[1]);
}
