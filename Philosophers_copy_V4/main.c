
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 00:00:00 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/15 00:00:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (validate_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (printf("Error initializing data or philosophers\n"));
	if (data.num_philos == 1)
		return (handle_single_philo(&data));
	create_threads(&data, &monitor_thread);
	join_threads(&data, monitor_thread);
	cleanup_resources(&data);
	return (0);
}
