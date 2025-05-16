
#include "philo.h"

static int validate_args(int argc, char **argv) {
    if (argc < 5 || argc > 6)
        return (printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat_count]\\n"));
    for (int i = 1; i < argc; i++) {
        for (int j = 0; argv[i][j]; j++) {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (printf("Error: Arguments must be positive integers\\n"));
        }
    }
    return (0);
}

int main(int argc, char **argv) {
    t_data data;
    pthread_t monitor_thread;

    if (validate_args(argc, argv))
        return (1);
    if (init_data(&data, argc, argv))
        return (printf("Error initializing data or philosophers\\n"));

    pthread_create(&monitor_thread, NULL, monitor_routine, &data);

    for (int i = 0; i < data.num_philos; i++) {
        pthread_create(&data.philos[i].thread, NULL, philosopher_routine, &data.philos[i]);
    }

    pthread_join(monitor_thread, NULL);
    for (int i = 0; i < data.num_philos; i++)
        pthread_join(data.philos[i].thread, NULL);

    for (int i = 0; i < data.num_philos; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.print_lock);
    free(data.forks);
    free(data.philos);

    return (0);
}
