/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:44 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/16 13:42:44 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// void	time_init(t_time *time)
// {
// 	gettimeofday(&(time->last_meal), NULL);
// 	gettimeofday(&(time->time_now_death), NULL);
// }

int		ft_log(t_philo *philo, char *event, int exception)
{
	long	time;
	char	*ptr;
	char	buff[128];

	ptr = buff;
	time = get_time() - philo->input->start;
	ft_putnbr_buff(time ,&ptr);
	ft_putstr_buff("ms philo" ,&ptr);
	ft_putnbr_buff(philo->id, &ptr);
	if (event == NULL)
	{
		if (philo->state == eating)
			ft_putstr_buff(" started eating", &ptr);
		else if (philo->state == sleeping)
			ft_putstr_buff(" started sleeping", &ptr);
		else if (philo->state == thinking)
			ft_putstr_buff(" started thinking", &ptr);
	}
	else
		ft_putstr_buff(event, &ptr);
	*ptr = '\0';
	pthread_mutex_lock(philo->mutex_print);
	ft_putendl_fd(buff, 1);
	pthread_mutex_unlock(philo->mutex_print);
	return (1);
}
