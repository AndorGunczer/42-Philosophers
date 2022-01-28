/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:29 by agunczer          #+#    #+#             */
/*   Updated: 2022/01/28 16:33:20 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	increase_philo_id(t_shared *shared, int *philo_id)
{
	pthread_mutex_lock(&shared->mutex_philo_id);
	*philo_id = shared->philo_id;
	shared->philo_id++;
	pthread_mutex_unlock(&shared->mutex_philo_id);
}

static int	check_input(int argc, char **argv)
{
	int	num;

	num = 1;
	if (argc < 5 || argc > 6)
	{
		printf("\033[0;31m\tWrong number of Arguments\n\tPhilosophers quit.");
		return (1);
	}
	if (is_num(argv[1]) == 0)
		num = 0;
	if (is_num(argv[2]) == 0)
		num = 0;
	if (is_num(argv[3]) == 0)
		num = 0;
	if (is_num(argv[4]) == 0)
		num = 0;
	if (argc == 6)
	{
		if (is_num(argv[5]) == 0)
			num = 0;
	}
	if (num == 1)
	{
		printf("\033[0;33mBUCKLE UP FUCKERS, THE HUNGER GAMES ARE ABOUT TO BEGIN!\n\033[0m");
		sleep(4);
	}
	else
	{
		printf("\033[0;31m\tWrong argument type provided\n\tPhilosophers quit.");
		return (1);
	}
	return (0);
}

static void	init_mutex(t_shared *shared_data)
{
	pthread_mutex_init(&shared_data->mutex_philo_id, NULL);
	pthread_mutex_init(&shared_data->mutex_forks, NULL);
	pthread_mutex_init(&shared_data->mutex_waiter, NULL);
	pthread_mutex_init(&shared_data->mutex_death, NULL);
	pthread_mutex_init(&shared_data->mutex_print, NULL);
}

static int	init_shared_data(t_shared *shared_data, char **argv)
{
	int	i;

	i = 0;
	shared_data->death = 0;
	shared_data->philo_id = 1;
	shared_data->number_of_philosophers = ft_atoi(argv[1]);
	shared_data->time_to_die = ft_atoi(argv[2]);
	shared_data->time_to_eat = ft_atoi(argv[3]);
	shared_data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		shared_data->number_of_meals = ft_atoi(argv[5]);
	else
		shared_data->number_of_meals = -1;
	shared_data->fork = malloc(shared_data->number_of_philosophers
			* sizeof(int));
	while (i < shared_data->number_of_philosophers)
	{
		shared_data->fork[i] = 1;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_shared	shared_data;
	pthread_t	*threads;

	i = 1;
	if (check_input(argc, argv) == 1)
		return (1);
	init_shared_data(&shared_data, argv);
	init_mutex(&shared_data);
	threads = malloc(shared_data.number_of_philosophers * sizeof(pthread_t));
	gettimeofday(&shared_data.timestamp, NULL);
	shared_data.start = (shared_data.timestamp.tv_sec * 1000)
		+ (shared_data.timestamp.tv_usec / 1000);
	while (i <= shared_data.number_of_philosophers)
	{
		pthread_create(&threads[i - 1], NULL, live_life, &shared_data);
		i++;
	}
	i = 1;
	while (i <= shared_data.number_of_philosophers)
	{
		pthread_join(threads[i - 1], NULL);
		i++;
	}
}
