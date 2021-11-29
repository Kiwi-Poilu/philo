#include "../include/philo.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\r'
		|| c == '\t' || c == '\n' || c == '\v')
		return (1);
	return (0);
}

int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

void print_params(t_params *params)
{
	printf("nb of philos = %d\n", params->nb_of_philos);
	printf("time to die = %d\n", params->time_to_die);
	printf("time to eat = %d\n", params->time_to_eat);
	printf("time to sleep  = %d\n", params->time_to_sleep);
	printf("nb of meals = %d\n", params->nb_of_meals);
}