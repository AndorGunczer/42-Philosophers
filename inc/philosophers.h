/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:09:50 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/10 10:51:00 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# include <stdlib.h>

# define TAKEN 0
# define AVAILABLE 1

// typedef struct s_shared {
// 	int				*fork;
// 	int				death;
// 	int				philo_id;
// 	pthread_mutex_t	mutex_forks;
// 	pthread_mutex_t	mutex_waiter;
// 	pthread_mutex_t	mutex_death;
// 	pthread_mutex_t	mutex_print;
// 	struct timeval	timestamp;
// 	double			start;
// }	t_shared;

typedef struct s_time {
	struct timeval	last_meal;
	struct timeval	time_now_death;
	struct timeval	time_now_occupation;
	struct timeval	occupation_start;
	int				number_of_meals;
}	t_time;

typedef struct s_input {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	struct timeval	timestamp;
	double			start;
}	t_input;

typedef struct s_philo {
	int				id;
	int				amount_meal;
	volatile int	*death;
	int				*lfork;
	int				*rfork;
	pthread_mutex_t	*mutex_lfork;
	pthread_mutex_t *mutex_rfork;
	pthread_mutex_t	*mutex_waiter;
	pthread_mutex_t	*mutex_death;
	pthread_mutex_t	*mutex_print;
	t_input			*input;
	pthread_t		philosopher;
	// t_time			time;
}	t_philo;

/*	death.c */
int		check_other_dead(t_philo *philo);
int		is_dead(t_time *time, t_philo *philo);

/*	forks.c */
// int		waiter(t_shared *shared, int forks_to_take[2]);
void	handle_forks_up(t_philo *philo, t_time *time);
void	handle_forks_down(t_philo *philo);

/*  utlis.c */
int		ft_atoi(const char *str);
int		ft_log(t_philo *philo, char *event, int exception);
int		is_num(char *str);
void	time_init(t_time *time);

/*  philo.c */
int		fill_philosophers(t_input *input, t_philo *philo, int i);
t_philo	*create_philosopher(t_input *input);
void	*live_life(void *arg);

/*  main.c */

/*	time.c */
long		get_time(struct timeval time);

#endif