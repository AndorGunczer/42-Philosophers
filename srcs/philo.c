#include "../inc/philosophers.h"

int		fill_philosophers(t_input input, t_philo *philo, int i)
{
	while (i < input.num_of_philo)
	{
		philo[i].mutex_rfork = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (philo[i].mutex_rfork == NULL)
			return (1);
		i++;
	}
	i = 0;
	while (i < input.num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].death = philo[0].death;
		philo[i].mutex_waiter = philo[0].mutex_waiter;
		philo[i].mutex_death = philo[0].mutex_death;
		philo[i].mutex_print = philo[0].mutex_print;
		philo[i].mutex_lfork = philo[(i + 1) % input.num_of_philo].mutex_rfork;
		philo[i].input = input.number_of_meals;
		i++;
	}
	i = 0;
	while (i < input.num_of_philo)
	{
		pthread_create(&philo[i].philosopher, NULL, &live_life, &philo[i]);
		i++;
	}
}

t_philo	*create_philosopher(t_input input)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *) malloc(input.num_of_philo * sizeof(t_philo));
	philo->death = (int *) malloc(sizeof(int));
	philo->mutex_waiter = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	philo->mutex_death = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	philo->mutex_print = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (philo->death == NULL || philo->mutex_waiter == NULL
		|| philo->mutex_death == NULL || philo->mutex_print == NULL)
		return (NULL);
	if (pthread_mutex_init(philo->mutex_waiter, NULL))
		return (NULL);
	if (pthread_mutex_init(philo->mutex_death, NULL))
		return (NULL);
	if (pthread_mutex_init(philo->mutex_print, NULL))
		return (NULL);
	philo->death = 0;
	i = 0;
	if (fill_philosophers(input, philo, i))
		return (NULL);
	return (philo);


}