/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:11:18 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/10 16:25:45 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// int	waiter(t_philo *philo)
// {
// 	int	fork_status;

// 	fork_status = AVAILABLE;
// 	if (*(philo->lfork) == 0)
// 		fork_status = TAKEN;
// 	if (*(philo->rfork) == 0)
// 		fork_status = TAKEN;
// 	return (fork_status);
// }

void	handle_forks_up(t_philo *philo, t_time *time)
{
	int	fork_status;

	if (is_dead(time, philo))
		return ;
		if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->mutex_lfork);
		ft_log(philo, "HAS TAKEN A FORK\n", 0);
		pthread_mutex_lock(philo->mutex_rfork);
		ft_log(philo, "HAS TAKEN A FORK\n", 0);
	}
	else
	{
		pthread_mutex_lock(philo->mutex_rfork);
		ft_log(philo, "HAS TAKEN A FORK\n", 0);
		pthread_mutex_lock(philo->mutex_lfork);
		ft_log(philo, "HAS TAKEN A FORK\n", 0);
	}
}

void	handle_forks_down(t_philo *philo)
{
		pthread_mutex_unlock(philo->mutex_rfork);
		pthread_mutex_unlock(philo->mutex_lfork);
}
