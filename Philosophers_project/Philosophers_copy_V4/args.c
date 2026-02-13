/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/15 00:00:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_philos time_to_die time_to_eat ");
		printf("time_to_sleep [must_eat_count]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (check_numeric(argv[i]))
		{
			printf("Error: Arguments must be positive integers\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_single_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	smart_sleep(data->time_to_die);
	printf("%ld 1 died\n", data->time_to_die);
	free(data->forks);
	free(data->philos);
	return (0);
}

void	cleanup_resources(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	free(data->forks);
	free(data->philos);
}
