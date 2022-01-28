/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:39 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/28 14:33:49 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philosophers.h"

void	eat(t_shared *shared, int philo_id, int forks_to_take[2], t_time *time)
{
	gettimeofday(&(time->occupation_start), NULL);
	gettimeofday(&(time->time_now_occupation), NULL);
	ft_log(shared, philo_id, "HAS STARTED EATING\n", 0);
	while ((time->time_now_occupation.tv_sec * 1000 + time->time_now_occupation.tv_usec / 1000) - (time->occupation_start.tv_sec * 1000 + time->occupation_start.tv_usec / 1000) < shared->time_to_eat)
	{
		gettimeofday(&(time->time_now_occupation), NULL);
	}
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

void	tasking(t_shared *shared, int philo_id, int forks_to_take[2], t_time *time)
{
	while (1)
	{
		if (check_other_dead(shared))
			break ;
		else
			handle_forks_up(shared, philo_id, forks_to_take, time);
		if (check_other_dead(shared))
			break ;
		else
		{
			gettimeofday(&(time->last_meal), NULL);
			eat(shared, philo_id, forks_to_take, time);
		}
		handle_forks_down(shared, philo_id, forks_to_take, time);
		if (check_other_dead(shared))
			break ;
		else
			rest(shared, philo_id, forks_to_take, time);
		ft_log(shared, philo_id, "HAS STARTED THINKING\n", 0);
	}
}

void	*live_life(void *arg)
{
	t_shared	*shared;
	int			philo_id;
	int			forks_to_take[2];
	t_time		time;


	shared = arg;
	increase_philo_id(shared, &philo_id);
	forks_to_take[0] = philo_id - 1;
	if (philo_id == shared->number_of_philosophers)
		forks_to_take[1] = 0;
	else
		forks_to_take[1] = philo_id;
	time_init(&time);
	tasking(shared, philo_id, forks_to_take, &time);
	return (NULL);
}