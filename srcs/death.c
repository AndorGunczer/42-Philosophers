/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:24 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/16 06:55:22 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// printf("%ld\n%ld\n", (time->time_now_death.tv_sec * 1000 + time->time_now_death.tv_usec / 1000) 
//- (time->last_meal.tv_sec * 1000 + time->last_meal.tv_usec / 1000), shared->time_to_die);

int	is_dead(t_time *time, t_philo *philo)
{
	gettimeofday(&(time->time_now_death), NULL);
	if (((time->time_now_death.tv_sec * 1000
				+ time->time_now_death.tv_usec / 1000)
			- (time->last_meal.tv_sec * 1000
				+ time->last_meal.tv_usec / 1000) > philo->input->time_to_die)
		&& *philo->death != 1)
	{
		(*philo->death)++;
		ft_log(philo, "DIED\n", 1);
		return (1);
	}
	return (0);
}
