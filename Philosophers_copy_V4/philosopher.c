
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/15 00:00:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_data *data, int id, const char *msg)
{
	pthread_mutex_lock(&data->print_lock);
	if (!data->is_dead && !data->all_eaten)
		printf("%ld %d %s\n", get_time_diff(data->start_time), id, msg);
	pthread_mutex_unlock(&data->print_lock);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_over(data))
	{
		log_status(data, philo->id, "is thinking");
		eat(philo);
		if (is_simulation_over(data))
			break ;
		log_status(data, philo->id, "is sleeping");
		smart_sleep(data->time_to_sleep);
	}
	return (NULL);
}
