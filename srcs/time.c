/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:39:48 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/16 07:14:09 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	get_time()
{
		struct	timeval	time;
		long	miliseconds;

		gettimeofday(&time, NULL);
		miliseconds = time.tv_sec * 1000;
		miliseconds += time.tv_usec / 1000;
		return (miliseconds);
}

int		ft_sleep(long duration, t_philo *philo)
{
	long	start;
	long	now;

	start = get_time();
	now = get_time();
	while (now - start < duration)
	{
		now = get_time();
		continue ;
	}
	return (0);
}