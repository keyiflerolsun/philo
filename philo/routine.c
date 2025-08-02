/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:01:26 by osancak           #+#    #+#             */
/*   Updated: 2025/08/02 16:09:14 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_alive(void *args)
{
	t_vars	*vars;
	t_philo	*philo;
	int		i;

	vars = args;
	while (vars->all_is_well)
	{
		i = -1;
		while (++i < vars->count)
		{
			philo = &vars->philos[i];
			if (get_time_ms() - philo->last_meal > philo->tt_die)
			{
				pthread_mutex_lock(&vars->death_mutex);
				vars->all_is_well = 0;
				pthread_mutex_unlock(&vars->death_mutex);
				log_status(&vars->philos[i], "died");
				return (NULL);
			}
		}
		usleep(500);
	}
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!is_dead(philo))
			log_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		if (!is_dead(philo))
			log_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!is_dead(philo))
			log_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		if (!is_dead(philo))
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
	if (is_dead(philo))
		return ;
	log_status(philo, "is eating");
	philo->last_meal = get_time_ms();
	usleep(philo->tt_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	op_arg(t_philo *philo)
{
	if (philo->vars->op_arg)
	{
		pthread_mutex_lock(&philo->vars->death_mutex);
		philo->must_eat--;
		pthread_mutex_unlock(&philo->vars->death_mutex);
		if (!philo->must_eat)
			return (1);
	}
	return (0);
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
		if (is_dead(philo) || op_arg(philo))
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
