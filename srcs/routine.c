#include "../inc/philosophers.h"

void	eat(t_philo *philo, t_time *time)
{
	gettimeofday(&(time->occupation_start), NULL);
	gettimeofday(&(time->time_now_occupation), NULL);
	ft_log(philo, "HAS STARTED EATING\n", 0);
	while ((time->time_now_occupation.tv_sec * 1000
			+ time->time_now_occupation.tv_usec / 1000)
		- (time->occupation_start.tv_sec * 1000
			+ time->occupation_start.tv_usec / 1000) < philo->input->time_to_eat)
	{
		gettimeofday(&(time->time_now_occupation), NULL);
	}
}

void	rest(t_philo *philo, t_time *time)
{
	gettimeofday(&(time->occupation_start), NULL);
	gettimeofday(&(time->time_now_occupation), NULL);
	ft_log(philo, "HAS STARTED SLEEPING\n", 0);
	while ((time->time_now_occupation.tv_sec * 1000
			+ time->time_now_occupation.tv_usec / 1000)
		- (time->occupation_start.tv_sec * 1000 + time->occupation_start.tv_usec
			/ 1000) < philo->input->time_to_sleep)
	{
		pthread_mutex_lock(&philo->mutex_death);
		if (is_dead(time, philo))
		{
			pthread_mutex_unlock(&philo->mutex_death);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex_death);
		gettimeofday(&(time->time_now_occupation), NULL);
	}
}

void	tasking(t_philo *philo, t_time *time)
{
	while (1 && time->number_of_meals != 0)
	{
		if (check_other_dead(philo))
			break ;
		else
			handle_forks_up(philo, time);
		if (check_other_dead(philo))
			break ;
		else
		{
			gettimeofday(&(time->last_meal), NULL);
			eat(philo, time);
		    philo->amount_meal--;
		}
		handle_forks_down(philo, time);
		if (check_other_dead(philo))
			break ;
		else
			rest(philo, time);
		ft_log(philo, "HAS STARTED THINKING\n", 0);
	}
}

void	*live_life(void *arg)
{
    t_philo *philo = arg;
	t_time		time;

	time_init(&time);
	tasking(philo, &time);
	return (NULL);
}
