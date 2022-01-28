/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:11:18 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/28 14:36:00 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philosophers.h"

void	handle_forks_up(t_shared *shared, int philo_id, int forks_to_take[2], t_time *time)
{
	int	fork_status;

	while(fork_status != AVAILABLE && shared->death == 0)
	{
		pthread_mutex_lock(&shared->mutex_death);
		if (is_dead(time, shared, philo_id))
		{
			pthread_mutex_unlock(&shared->mutex_death);	
			return ;
		}
		pthread_mutex_unlock(&shared->mutex_death);
		pthread_mutex_lock(&shared->mutex_waiter);
		fork_status = waiter(shared, forks_to_take);
		if (fork_status == AVAILABLE)
		{
			shared->fork[forks_to_take[0]] = 0;
			ft_log(shared, philo_id, "HAS TAKEN A FORK\n", 0);
			shared->fork[forks_to_take[1]] = 0;
			ft_log(shared, philo_id, "HAS TAKEN A FORK\n", 0);
		}
		pthread_mutex_unlock(&shared->mutex_waiter);
	}
}

void	handle_forks_down(t_shared *shared, int philo_id, int forks_to_take[2], t_time *time)
{
	pthread_mutex_lock(&shared->mutex_forks);
	shared->fork[forks_to_take[0]] = 1;
	shared->fork[forks_to_take[1]] = 1;
	pthread_mutex_unlock(&shared->mutex_forks);
}