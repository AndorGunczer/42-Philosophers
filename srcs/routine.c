#include "../inc/philosophers.h"

static int		eat(t_philo *philo)
{
	philo->state = eating;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->mutex_lfork);
		ft_log(philo, " has taken a fork", 0);
		if (*philo->death == 1)
			return (1);
		pthread_mutex_lock(philo->mutex_rfork);
		ft_log(philo, " has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(philo->mutex_rfork);
		ft_log(philo, " has taken a fork", 0);
		if (*philo->death == 1)
			return (1);
		pthread_mutex_lock(philo->mutex_lfork);
		ft_log(philo, " has taken a fork", 0);
	}
	if (ft_sleep(philo->input->time_to_eat, philo) == 1)
		return (1);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->mutex_rfork);
	pthread_mutex_unlock(philo->mutex_lfork);
	return (0);
}

static int		ft_sleeping(t_philo *philo)
{
	philo->state = sleeping;
	if (ft_sleep(philo->input->time_to_sleep, philo) == 1)
		return (1);
	return (0);
}

static int		think(t_philo *philo)
{
	philo->state = thinking;
	if (*(philo->death) == 1)
		return (1);
	usleep(150);
	return (0);
}

void	*routine(void *arg)
{
    t_philo *philo = arg;

	if (philo->id % 2 == 0)
		think(philo);
	while (1)
	{
		if (eat(philo) == 1)
			break ;
		if (philo->amount_meal++ == philo->input->number_of_meals)
			break ;
		if (ft_sleeping(philo) == 1)
			break ;
		if (think(philo) == 1)
			break ;
	}
	pthread_mutex_unlock(philo->mutex_lfork);
	pthread_mutex_unlock(philo->mutex_rfork);
	return (NULL);
}
