# include "../inc/philosophers.h"

static int     waiter(t_shared *shared, int philo_id, int forks_to_take[2])
{
    int fork_status;

    fork_status = AVAILABLE;
    if (shared->fork[forks_to_take[0]] == 0)
        fork_status = TAKEN;
    if (shared->fork[forks_to_take[1]] == 0)
        fork_status = TAKEN;
    return (fork_status);
}

void    take_forks(t_shared *shared, int philo_id, int forks_to_take[2])
{
    int fork_status;

    while(fork_status != AVAILABLE)
    {
        pthread_mutex_lock(&shared->mutex_waiter);
        fork_status = waiter(shared, philo_id, forks_to_take);
        if (fork_status == AVAILABLE)
        {
            shared->fork[forks_to_take[0]] = 0;
            shared->fork[forks_to_take[1]] = 0;
        }
        pthread_mutex_unlock(&shared->mutex_waiter);
    }
    printf("PHILO%d_IS_EATING | TAKEN FORKS : %d and %d\n", philo_id, forks_to_take[0], forks_to_take[1]);
    // usleep(shared->time_to_eat);
    sleep(1);
    // while (1)
    // {
    //     if (...)
    //         break
    // }
    pthread_mutex_lock(&shared->mutex_forks);
    shared->fork[forks_to_take[0]] = 1;
    shared->fork[forks_to_take[1]] = 1;
    pthread_mutex_unlock(&shared->mutex_forks);
}

void    *live_life(void *arg)
{
    t_shared *shared;
    int     philo_id;
    int     forks_to_take[2];

    shared = arg;
    increase_philo_id(shared, &philo_id);
    forks_to_take[0] = philo_id - 1;
    if (philo_id == shared->number_of_philosophers)
        forks_to_take[1] = 0;
    else
        forks_to_take[1] = philo_id;
    take_forks(shared, philo_id, forks_to_take);

    return (NULL);
}