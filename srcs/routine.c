#include "../inc/philosophers.h"

void	eat(t_philo *philo, t_time *time)
{
	long	start;

	usleep(200);
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

	usleep(200);
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
	// if (philo->id % 2 == 0)
	// 		usleep(500);
	while (1 && philo->amount_meal != 0)
	{
		if (philo->id % 2 == 0)
			usleep(500);
		if (*(philo->death) == 0)
			handle_forks_up(philo, time);
		else
			break ;
		if (*(philo->death) == 0)
		{
			eat(philo, time);
			if (philo->amount_meal > 0)
			philo->amount_meal--;
		}
		else
			break;
		handle_forks_down(philo);
		gettimeofday(&(time->last_meal), NULL);
		if (*(philo->death) == 0)
			rest(philo, time);
		else
			break ;
		ft_log(philo, "HAS STARTED THINKING\n", 0);
		// usleep(200);
	}
	handle_forks_down(philo);
}

void	*live_life(void *arg)
{
    t_philo *philo = arg;
	t_time		time;

	time_init(&time);
	tasking(philo, &time);
	return (NULL);
}
