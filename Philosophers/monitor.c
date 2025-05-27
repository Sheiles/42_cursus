

#include "philo.h"

void *monitor_routine(void *arg) {
    t_data *data = (t_data *)arg;
    int i;
    long current_time;

    while (!data->is_dead) {
        i = 0;
        while (i < data->num_philos) {
            current_time = get_time();
            pthread_mutex_lock(&data->print_lock);
            if ((current_time - data->philos[i].last_meal) >= data->time_to_die) {
                data->is_dead = 1;
                printf("%ld %d died\n", current_time, data->philos[i].id);
                pthread_mutex_unlock(&data->print_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&data->print_lock);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}