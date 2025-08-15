/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/15 00:00:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo)
{
	t_data	*data;
	int		left_fork;
	int		right_fork;

	data = philo->data;
	left_fork = philo->id - 1;
	right_fork = philo->id % data->num_philos;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[right_fork]);
		log_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[left_fork]);
		log_status(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[left_fork]);
		log_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[right_fork]);
		log_status(data, philo->id, "has taken a fork");
	}
}

void	release_forks(t_philosopher *philo)
{
	t_data	*data;
	int		left_fork;
	int		right_fork;

	data = philo->data;
	left_fork = philo->id - 1;
	right_fork = philo->id % data->num_philos;
	pthread_mutex_unlock(&data->forks[left_fork]);
	pthread_mutex_unlock(&data->forks[right_fork]);
}

void	eat(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	take_forks(philo);
	log_status(data, philo->id, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_diff(data->start_time);
	pthread_mutex_unlock(&philo->meal_lock);
	smart_sleep(data->time_to_eat);
	philo->meals_eaten++;
	release_forks(philo);
}
