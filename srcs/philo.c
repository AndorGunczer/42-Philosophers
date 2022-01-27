# include "../inc/philosophers.h"

static void log(t_shared *shared, int philo_id, char *event)
{
    double   fresh;
    gettimeofday(shared->timestamp, NULL);
    fresh = shared->timestamp->tv_sec * 1000000 + shared->timestamp->tv_usec;
    printf("%f philo %d %s", (fresh - shared->start) / 1000, philo_id, event);
}

static int     waiter(t_shared *shared, int forks_to_take[2])
{
    int fork_status;

    fork_status = AVAILABLE;
    if (shared->fork[forks_to_take[0]] == 0)
        fork_status = TAKEN;
    if (shared->fork[forks_to_take[1]] == 0)
        fork_status = TAKEN;
    return (fork_status);
}

void    eat(t_shared *shared, int philo_id, int forks_to_take[2], struct timeval *start, struct timeval *now)
{
	gettimeofday(start, NULL);
	gettimeofday(now, NULL);
    log(shared, philo_id, "HAS STARTED EATING\n");
	while ((now->tv_sec * 1000000 + now->tv_usec) - (start->tv_sec * 1000000 +  start->tv_usec) < shared->time_to_eat)
	{
		gettimeofday(now, NULL);
	}
	// printf("%ld\n", now->tv_sec - 10000000000);
    // usleep(100000);
}

void	rest(t_shared *shared, int philo_id, int forks_to_take[2], struct timeval *start, struct timeval *now)
{
	gettimeofday(start, NULL);
	gettimeofday(now, NULL);
    log(shared, philo_id, "HAS STARTED SLEEPING\n");
	while ((now->tv_sec * 1000000 + now->tv_usec) - (start->tv_sec * 1000000 +  start->tv_usec) < shared->time_to_sleep)
	{
		gettimeofday(now, NULL);
	}
}

void    handle_forks(t_shared *shared, int philo_id, int forks_to_take[2], int task)
{
    int fork_status;

    if (task == PICK_UP)
    {
        while(fork_status != AVAILABLE)
        {
            pthread_mutex_lock(&shared->mutex_waiter);
            fork_status = waiter(shared, forks_to_take);
            if (fork_status == AVAILABLE)
            {
                shared->fork[forks_to_take[0]] = 0;
                log(shared, philo_id, "HAS TAKEN A FORK\n");
                shared->fork[forks_to_take[1]] = 0;
                log(shared, philo_id, "HAS TAKEN A FORK\n");
            }
            pthread_mutex_unlock(&shared->mutex_waiter);
        }
    }
    else if (task == PUT_DOWN)
    {
        pthread_mutex_lock(&shared->mutex_forks);
        shared->fork[forks_to_take[0]] = 1;
        shared->fork[forks_to_take[1]] = 1;
        pthread_mutex_unlock(&shared->mutex_forks);
    }
}

void    *live_life(void *arg)
{
    t_shared        *shared;
    int             philo_id;
    int             forks_to_take[2];
	struct timeval	time_now;
	struct timeval	time_start;


    shared = arg;
    increase_philo_id(shared, &philo_id);
    forks_to_take[0] = philo_id - 1;
    if (philo_id == shared->number_of_philosophers)
        forks_to_take[1] = 0;
    else
        forks_to_take[1] = philo_id;
    while (1)
    {
        handle_forks(shared, philo_id, forks_to_take, PICK_UP);
        eat(shared, philo_id, forks_to_take, &time_start, &time_now);
        handle_forks(shared, philo_id, forks_to_take, PUT_DOWN);
        rest(shared, philo_id, forks_to_take, &time_start, &time_now);
        log(shared, philo_id, "HAS STARTED THINKING\n");
    }
    return (NULL);
}