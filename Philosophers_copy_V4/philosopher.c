
#include "philo.h"

void log_status(t_data *data, int id, const char *msg) {
    pthread_mutex_lock(&data->print_lock);
    if (!data->is_dead && !data->all_eaten) {
        printf("%ld %d %s\n", get_time_diff(data->start_time), id, msg);
    }
    pthread_mutex_unlock(&data->print_lock);
}

void take_forks(t_philosopher *philo) {
    t_data *data = philo->data;
    int left_fork = philo->id - 1;
    int right_fork = philo->id % data->num_philos;

    // Prevent deadlock by ordering fork acquisition
    if (philo->id % 2 == 0) {
        pthread_mutex_lock(&data->forks[right_fork]);
        log_status(data, philo->id, "has taken a fork");
        pthread_mutex_lock(&data->forks[left_fork]);
        log_status(data, philo->id, "has taken a fork");
    } else {
        pthread_mutex_lock(&data->forks[left_fork]);
        log_status(data, philo->id, "has taken a fork");
        pthread_mutex_lock(&data->forks[right_fork]);
        log_status(data, philo->id, "has taken a fork");
    }
}

void release_forks(t_philosopher *philo) {
    t_data *data = philo->data;
    int left_fork = philo->id - 1;
    int right_fork = philo->id % data->num_philos;

    pthread_mutex_unlock(&data->forks[left_fork]);
    pthread_mutex_unlock(&data->forks[right_fork]);
}

void eat(t_philosopher *philo) {
    t_data *data = philo->data;
    
    take_forks(philo);
    log_status(data, philo->id, "is eating");
    
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal = get_time_diff(data->start_time);
    pthread_mutex_unlock(&philo->meal_lock);
    
    smart_sleep(data->time_to_eat);
    philo->meals_eaten++;
    release_forks(philo);
}

void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;

    // Stagger start for even philosophers to prevent deadlock
    if (philo->id % 2 == 0)
        usleep(1000);

    while (!is_simulation_over(data)) {
        log_status(data, philo->id, "is thinking");
        eat(philo);
        if (is_simulation_over(data))
            break;
        log_status(data, philo->id, "is sleeping");
        smart_sleep(data->time_to_sleep);
    }
    return (NULL);
}
