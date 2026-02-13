

#include "philo.h"

int check_death(t_data *data, int i) {
    long current_time;
    long last_meal;
    
    pthread_mutex_lock(&data->philos[i].meal_lock);
    last_meal = data->philos[i].last_meal;
    pthread_mutex_unlock(&data->philos[i].meal_lock);
    
    current_time = get_time_diff(data->start_time);
    
    if ((current_time - last_meal) >= data->time_to_die) {
        pthread_mutex_lock(&data->death_lock);
        data->is_dead = 1;
        pthread_mutex_unlock(&data->death_lock);
        
        pthread_mutex_lock(&data->print_lock);
        printf("%ld %d died\n", current_time, data->philos[i].id);
        pthread_mutex_unlock(&data->print_lock);
        return (1);
    }
    return (0);
}

int check_all_eaten(t_data *data) {
    int i;
    int all_finished;

    if (data->must_eat_count == -1)
        return (0);

    all_finished = 1;
    i = 0;
    while (i < data->num_philos) {
        if (data->philos[i].meals_eaten < data->must_eat_count) {
            all_finished = 0;
            break;
        }
        i++;
    }

    if (all_finished) {
        pthread_mutex_lock(&data->death_lock);
        data->all_eaten = 1;
        pthread_mutex_unlock(&data->death_lock);
        return (1);
    }
    return (0);
}

void *monitor_routine(void *arg) {
    t_data *data = (t_data *)arg;
    int i;

    while (!is_simulation_over(data)) {
        i = 0;
        while (i < data->num_philos && !is_simulation_over(data)) {
            if (check_death(data, i))
                return (NULL);
            i++;
        }
        
        if (check_all_eaten(data))
            return (NULL);
            
        usleep(1000);
    }
    return (NULL);
}