/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:44 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/28 14:09:45 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philosophers.h"

static	int	ft_isspace(char c);

void	time_init(t_time *time)
{
	gettimeofday(&(time->last_meal), NULL);
	gettimeofday(&(time->time_now_death), NULL);
}

int		waiter(t_shared *shared, int forks_to_take[2])
{
	int	fork_status;

	fork_status = AVAILABLE;
	if (shared->fork[forks_to_take[0]] == 0)
		fork_status = TAKEN;
	if (shared->fork[forks_to_take[1]] == 0)
		fork_status = TAKEN;
	return (fork_status);
}


int	ft_log(t_shared *shared, int philo_id, char *event, int exception)
{
	double   fresh;

	pthread_mutex_lock(&shared->mutex_print);
	gettimeofday(&shared->timestamp, NULL);
	fresh = shared->timestamp.tv_sec * 1000 + shared->timestamp.tv_usec / 1000;
	if (shared->death == 0 || exception == 1)
		printf("%.0fms\tphilo %d\t\t%s", (fresh - shared->start), philo_id, event);
	pthread_mutex_unlock(&shared->mutex_print);

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