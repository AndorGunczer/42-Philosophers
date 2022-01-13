#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

# include <stdlib.h>

# define TAKEN 0
# define AVAILABLE 1

# define PICK_UP 0
# define PUT_DOWN 1

typedef struct s_shared {
    int *fork;
    int death;
    int philo_id;
    pthread_mutex_t mutex_philo_id;
    pthread_mutex_t mutex_forks;
    pthread_mutex_t mutex_waiter;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}   t_shared;

/*  utlis.c */
int	ft_atoi(const char *str);

/*  philo.c */
void *live_life(void *arg);

/*  main.c */
void    increase_philo_id(t_shared *shared, int *philo_id);

#endif