# include "../inc/philosophers.h"

int		check_other_dead(t_shared *shared)
{
	pthread_mutex_lock(&shared->mutex_death);
	if (shared->death == 0)
	{
		pthread_mutex_unlock(&shared->mutex_death);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&shared->mutex_death);
		return (1);
	}
}

int		is_dead(t_time *time, t_shared *shared, int philo_id)
{
	gettimeofday(&(time->time_now_death), NULL);
	if (((time->time_now_death.tv_sec * 1000 + time->time_now_death.tv_usec / 1000) - (time->last_meal.tv_sec * 1000 + time->last_meal.tv_usec / 1000) > shared->time_to_die) && shared->death != 1)
	{
		shared->death = 1;
		ft_log(shared, philo_id, "DIED\n", 1);
		return (1);
	}
	return (0);
}

void    eat(t_shared *shared, int philo_id, int forks_to_take[2], t_time *time)
{
	gettimeofday(&(time->occupation_start), NULL);
	gettimeofday(&(time->time_now_occupation), NULL);
    ft_log(shared, philo_id, "HAS STARTED EATING\n", 0);
	while ((time->time_now_occupation.tv_sec * 1000 + time->time_now_occupation.tv_usec / 1000) - (time->occupation_start.tv_sec * 1000 + time->occupation_start.tv_usec / 1000) < shared->time_to_eat)
	{
		gettimeofday(&(time->time_now_occupation), NULL);
	}
	gettimeofday(&(time->last_meal), NULL);
}

void	rest(t_shared *shared, int philo_id, int forks_to_take[2], t_time *time)
{
	gettimeofday(&(time->occupation_start), NULL);
	gettimeofday(&(time->time_now_occupation), NULL);
    ft_log(shared, philo_id, "HAS STARTED SLEEPING\n", 0);
	while ((time->time_now_occupation.tv_sec * 1000 + time->time_now_occupation.tv_usec / 1000) - (time->occupation_start.tv_sec * 1000 + time->occupation_start.tv_usec / 1000) < shared->time_to_sleep)
	{
		pthread_mutex_lock(&shared->mutex_death);
		if (is_dead(time, shared, philo_id))
		{
			pthread_mutex_unlock(&shared->mutex_death);	
			return ;
		}
		pthread_mutex_unlock(&shared->mutex_death);
		gettimeofday(&(time->time_now_occupation), NULL);
	}
}

void    handle_forks(t_shared *shared, int philo_id, int forks_to_take[2], int task)
{
    int fork_status;

    if (task == PICK_UP)
    {
        while(fork_status != AVAILABLE && shared->death == 0)
        {
			// if (is_dead(time, shared))
			// 	return ;
			// printf("HELLO");
            pthread_mutex_lock(&shared->mutex_waiter);
            fork_status = waiter(shared, forks_to_take);
            if (fork_status == AVAILABLE)
            {
                shared->fork[forks_to_take[0]] = 0;
                ft_log(shared, philo_id, "HAS TAKEN A FORK\n", 0);
                shared->fork[forks_to_take[1]] = 0;
                ft_log(shared, philo_id, "HAS TAKEN A FORK\n", 0);
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
	t_time			time;


    shared = arg;
    increase_philo_id(shared, &philo_id);
    forks_to_take[0] = philo_id - 1;
    if (philo_id == shared->number_of_philosophers)
        forks_to_take[1] = 0;
    else
        forks_to_take[1] = philo_id;
	time_init(&time);
    while (1)
    {
		if (check_other_dead(shared))
			return (NULL);
		else
        	handle_forks(shared, philo_id, forks_to_take, PICK_UP);
		if (check_other_dead(shared))
			return (NULL);
		else
        	eat(shared, philo_id, forks_to_take, &time);
        handle_forks(shared, philo_id, forks_to_take, PUT_DOWN);
		if (check_other_dead(shared))
			return (NULL);
		else
        	rest(shared, philo_id, forks_to_take, &time);
        ft_log(shared, philo_id, "HAS STARTED THINKING\n", 0);
		// return (NULL);
    }
    return (NULL);
}