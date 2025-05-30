
#include "philo.h"

long get_time(void) {
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void smart_sleep(long time_in_ms) {
    long start = get_time();
    while ((get_time() - start) < time_in_ms) {
        usleep(500);
    }
}
