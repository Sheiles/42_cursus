
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher {
    int                 id;
    pthread_t           thread;
    long                last_meal;
    int                 meals_eaten;
    struct s_data       *data;
} t_philosopher;

typedef struct s_data {
    int                 num_philos;
    long                time_to_die;
    long                time_to_eat;
    long                time_to_sleep;
    int                 must_eat_count;
    int                 is_dead;
    pthread_mutex_t     *forks;
    pthread_mutex_t     print_lock;
    t_philosopher       *philos;
} t_data;


int     init_data(t_data *data, int argc, char **argv);


void    *philosopher_routine(void *arg);


void    *monitor_routine(void *arg);


long    get_time(void);
void    smart_sleep(long time_in_ms);
void    log_status(t_data *data, int id, const char *msg);

#endif
