/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:44 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/16 07:14:42 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	time_init(t_time *time)
{
	gettimeofday(&(time->last_meal), NULL);
	gettimeofday(&(time->time_now_death), NULL);
}

int	ft_log(t_philo *philo, char *event, int exception)
{
	long	fresh;

	fresh = get_time();
	if (*philo->death == 0 || exception == 1)
		printf("%.0fms\tphilo %d\t\t%s", (fresh
				- philo->input->start), philo->id, event);
	// pthread_mutex_unlock(philo->mutex_print);
	return (1);
}
