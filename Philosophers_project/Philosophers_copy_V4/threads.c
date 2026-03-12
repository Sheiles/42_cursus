











#include "philo.h"

void	create_threads(t_data *data, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, 
			philosopher_routine, &data->philos[i]);
		i++;
	}
	pthread_create(monitor_thread, NULL, monitor_routine, data);
}

void	join_threads(t_data *data, pthread_t monitor_thread)
{
	int	i;

	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
