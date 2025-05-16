
#include "philo.h"

void log_status(t_data *data, int id, const char *msg) {
    pthread_mutex_lock(&data->print_lock);
    if (!data->is_dead) {
        printf("%ld %d %s\n", get_time(), id, msg);
    }
    pthread_mutex_unlock(&data->print_lock);
}

void take_forks(t_philosopher *philo) {
    t_data *data = philo->data;

    pthread_mutex_lock(&data->forks[philo->id - 1]);
    log_status(data, philo->id, "has taken a fork");

    pthread_mutex_lock(&data->forks[(philo->id) % data->num_philos]);
    log_status(data, philo->id, "has taken a fork");
}

void release_forks(t_philosopher *philo) {
    t_data *data = philo->data;
    pthread_mutex_unlock(&data->forks[philo->id - 1]);
    pthread_mutex_unlock(&data->forks[(philo->id) % data->num_philos]);
}

void eat(t_philosopher *philo) {
    t_data *data = philo->data;
    take_forks(philo);
    log_status(data, philo->id, "is eating");
    philo->last_meal = get_time();
    smart_sleep(data->time_to_eat);
    philo->meals_eaten++;
    release_forks(philo);
}

void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;

    while (!data->is_dead) {
        log_status(data, philo->id, "is thinking");
        eat(philo);
        log_status(data, philo->id, "is sleeping");
        smart_sleep(data->time_to_sleep);
    }
    return (NULL);
}
