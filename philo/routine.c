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
	int		i;

	vars = args;
	while (1)
	{
		i = 0;
		while (i < vars->count)
		{
			philo = &vars->philos[i];
			if (get_time_ms() - philo->last_meal > philo->tt_die)
			{
				log_status(philo, "died");
				vars->all_is_well = 0;
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

static void	eat_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		log_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		log_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		log_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		log_status(philo, "has taken a fork");
	}
	philo->last_meal = get_time_ms();
	log_status(philo, "is eating");
	usleep(philo->tt_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->vars->all_is_well)
	{
		if (philo->vars->count > 1)
			eat_routine(philo);
		if (!log_status(philo, "is sleeping"))
			break ;
		usleep(philo->tt_sleep * 1000);
		if (!log_status(philo, "is thinking"))
			break ;
	}
	return (NULL);
}
