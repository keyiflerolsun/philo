/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:01:26 by osancak           #+#    #+#             */
/*   Updated: 2025/07/28 17:52:09 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_alive(void *args)
{
	t_vars	*vars;
	t_philo	*philo;
	long	timestamp;
	int		i;

	vars = args;
	while (1)
	{
		i = 0;
		while (i < vars->count)
		{
			philo = &vars->philos[i];
			timestamp = get_time_ms(&vars->death_mutex);
			if (timestamp - philo->last_meal > philo->tt_die)
			{
				vars->all_is_well = 0;
				log_status(&vars->philos[i], "died");
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
}

static void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		log_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		log_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		log_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		log_status(philo, "has taken a fork");
	}
}

static void	eat_routine(t_philo *philo)
{
	if (philo->vars->count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		log_status(philo, "has taken a fork");
		usleep(philo->tt_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	take_forks(philo);
	log_status(philo, "is eating");
	philo->last_meal = get_time_ms(&philo->vars->death_mutex);
	usleep(philo->tt_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->id * 500);
	while (!is_dead(philo))
	{
		eat_routine(philo);
		if (is_dead(philo))
			break ;
		log_status(philo, "is sleeping");
		usleep(philo->tt_sleep * 1000);
		if (is_dead(philo))
			break ;
		log_status(philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}
