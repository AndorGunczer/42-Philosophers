/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:44 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/10 16:46:18 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	ft_isspace(char c);

void	time_init(t_time *time)
{
	gettimeofday(&(time->last_meal), NULL);
	gettimeofday(&(time->time_now_death), NULL);
}

int	is_num(char *str)
{
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (*str > 57 || *str < 48)
			return (0);
		str++;
	}
	return (1);
}

int	ft_log(t_philo *philo, char *event, int exception)
{
	double	fresh;

	pthread_mutex_lock(philo->mutex_print);
	gettimeofday(&(philo->input->timestamp), NULL);
	pthread_mutex_unlock(philo->mutex_print);
	fresh = philo->input->timestamp.tv_sec * 1000
		+ philo->input->timestamp.tv_usec / 1000;
	if (*philo->death == 0 || exception == 1)
		printf("%.0fms\tphilo %d\t\t%s", (fresh
				- philo->input->start), philo->id, event);
	// pthread_mutex_unlock(philo->mutex_print);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		j;
	int		num;

	i = 0;
	j = 0;
	num = 0;
	while (ft_isspace(*(str + i)) == 1 && str[i] != '\0')
	{
		i++;
		j++;
	}
	if (str[i] == '\0')
		return (0);
	if (*(str + j) == '-' || *(str + j) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		num = num * 10 + (*(str + i) - '0');
		i++;
	}
	if (*(str + j) == '-')
		num *= -1;
	return (num);
}

static	int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else if ((c == '\n' || c == '\t' || c == '\v' || c == '\t' || c == '\r'
			|| c == '\f'))
		return (1);
	else
		return (0);
}
