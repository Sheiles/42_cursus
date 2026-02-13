
#include "philo.h"

long get_time(void) {
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long get_time_diff(long start_time) {
    return (get_time() - start_time);
}

void smart_sleep(long time_in_ms) {
    long start = get_time();
    while ((get_time() - start) < time_in_ms) {
        usleep(500);
    }
}

int is_simulation_over(t_data *data) {
    pthread_mutex_lock(&data->death_lock);
    if (data->is_dead || data->all_eaten) {
        pthread_mutex_unlock(&data->death_lock);
        return (1);
    }
    pthread_mutex_unlock(&data->death_lock);
    return (0);
}
