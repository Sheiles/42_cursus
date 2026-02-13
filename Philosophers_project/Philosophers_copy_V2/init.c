#include "philo.h"

int init_data(t_data *data, int argc, char **argv) {
    int i;

    data->num_philos = atoi(argv[1]);
    data->time_to_die = atol(argv[2]);
    data->time_to_eat = atol(argv[3]);
    data->time_to_sleep = atol(argv[4]);
    data->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;
    data->is_dead = 0;
    data->all_eaten = 0;
    data->start_time = get_time();

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = malloc(sizeof(t_philosopher) * data->num_philos);

    if (!data->forks || !data->philos)
        return (1);

    pthread_mutex_init(&data->print_lock, NULL);
    pthread_mutex_init(&data->death_lock, NULL);

    i = 0;
    while (i < data->num_philos) {
        pthread_mutex_init(&data->forks[i], NULL);
        pthread_mutex_init(&data->philos[i].meal_lock, NULL);
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = 0;
        data->philos[i].data = data;
        i++;
    }
    return (0);
}