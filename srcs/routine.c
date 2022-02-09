#include "../inc/philosophers.h"

void	eat(t_philo *philo, t_time *time)
{
	long	start;

	ft_log(philo, "HAS STARTED EATING\n", 0);
	gettimeofday(&(time->occupation_start), NULL);
	start = (time->occupation_start.tv_sec * 1000 + time->occupation_start.tv_usec / 1000);
	while (get_time(time->time_now_occupation) - start < philo->input->time_to_eat)
	{
		if (is_dead(time, philo))
			return ;
	}
}

void	rest(t_philo *philo, t_time *time)
{
	long	start;

	ft_log(philo, "HAS STARTED SLEEPING\n", 0);
	gettimeofday(&(time->occupation_start), NULL);
	start = (time->occupation_start.tv_sec * 1000 + time->occupation_start.tv_usec / 1000);
	while (get_time(time->time_now_occupation)
		- start < philo->input->time_to_sleep)
	{
		if (is_dead(time, philo))
			return ;
	}
}

void	tasking(t_philo *philo, t_time *time)
{
	if (philo->id % 2 == 0)
			usleep(100);
	while (1 && philo->amount_meal != 0)
	{
		if (check_other_dead(philo))
		{
			handle_forks_down(philo, time);
			break ;
		}
		else
			handle_forks_up(philo, time);
		if (check_other_dead(philo))
		{
			handle_forks_down(philo, time);
			break ;
		}
		else
		{
			eat(philo, time);
			if (philo->amount_meal > 0)
			philo->amount_meal--;
		}
		handle_forks_down(philo, time);
		gettimeofday(&(time->last_meal), NULL);
		if (check_other_dead(philo))
		{
			handle_forks_down(philo, time);
			break ;
		}
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
