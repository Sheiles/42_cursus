
#include "philo.h"

void *monitor_routine(void *arg) {
    t_data *data = (t_data *)arg;

    while (!data->is_dead) {
        for (int i = 0; i < data->num_philos; i++) {
            long current_time = get_time();
            pthread_mutex_lock(&data->print_lock);
            if ((current_time - data->philos[i].last_meal) >= data->time_to_die) {
                data->is_dead = 1;
                printf("%ld %d died\n", current_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&data->print_lock);
            usleep(1000);
        }
    }
    return (NULL);
}
