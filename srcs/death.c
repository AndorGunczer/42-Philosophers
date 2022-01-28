/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:24 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/28 16:35:39 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_other_dead(t_shared *shared)
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

// printf("%ld\n%ld\n", (time->time_now_death.tv_sec * 1000 + time->time_now_death.tv_usec / 1000) 
//- (time->last_meal.tv_sec * 1000 + time->last_meal.tv_usec / 1000), shared->time_to_die);

int	is_dead(t_time *time, t_shared *shared, int philo_id)
{
	gettimeofday(&(time->time_now_death), NULL);
	if (((time->time_now_death.tv_sec * 1000
				+ time->time_now_death.tv_usec / 1000)
			- (time->last_meal.tv_sec * 1000
				+ time->last_meal.tv_usec / 1000) > shared->time_to_die)
		&& shared->death != 1)
	{
		shared->death = 1;
		ft_log(shared, philo_id, "DIED\n", 1);
		return (1);
	}
	return (0);
}
