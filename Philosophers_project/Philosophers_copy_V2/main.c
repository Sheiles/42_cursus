
#include "philo.h"

static int validate_args(int argc, char **argv) {
    int i = 1;
    if (argc < 5 || argc > 6)
        return (printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat_count]\n"));
    while (i < argc) {
        int j = 0;
        while (argv[i][j]) {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (printf("Error: Arguments must be positive integers\n"));
            j++;
        }
        i++;
    }
    return (0);
}

int main(int argc, char **argv) {
    t_data data;
    pthread_t monitor_thread;
    int i;

    if (validate_args(argc, argv))
        return (1);
    if (init_data(&data, argc, argv))
        return (printf("Error initializing data or philosophers\n"));

    // Handle single philosopher case
    if (data.num_philos == 1) {
        printf("0 1 has taken a fork\n");
        smart_sleep(data.time_to_die);
        printf("%ld 1 died\n", data.time_to_die);
        free(data.forks);
        free(data.philos);
        return (0);
    }

    i = 0;
    while (i < data.num_philos) {
        pthread_create(&data.philos[i].thread, NULL, philosopher_routine, &data.philos[i]);
        i++;
    }

    pthread_create(&monitor_thread, NULL, monitor_routine, &data);

    pthread_join(monitor_thread, NULL);

    i = 0;
    while (i < data.num_philos) {
        pthread_join(data.philos[i].thread, NULL);
        i++;
    }

    // Cleanup
    i = 0;
    while (i < data.num_philos) {
        pthread_mutex_destroy(&data.forks[i]);
        pthread_mutex_destroy(&data.philos[i].meal_lock);
        i++;
    }
    pthread_mutex_destroy(&data.print_lock);
    pthread_mutex_destroy(&data.death_lock);
    free(data.forks);
    free(data.philos);

    return (0);
}
