/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:01:26 by osancak           #+#    #+#             */
/*   Updated: 2025/08/03 20:15:42 by osancak          ###   ########.fr       */
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
			if (philo->vars->op_arg && !philo->must_eat)
				return (NULL);
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

static int	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		take_fork(philo, philo->left_fork);
		take_fork(philo, philo->right_fork);
	}
	else
	{
		take_fork(philo, philo->right_fork);
		take_fork(philo, philo->left_fork);
	}
	if (is_dead(philo))
		return (unlock_forks(philo));
	return (1);
}

static int	op_arg(t_philo *philo)
{
	if (philo->vars->op_arg)
	{
		if (!philo->must_eat)
			return (0);
		pthread_mutex_lock(&philo->vars->death_mutex);
		philo->must_eat--;
		pthread_mutex_unlock(&philo->vars->death_mutex);
		if (!philo->must_eat)
			return (0);
	}
	return (1);
}

static int	eat_routine(t_philo *philo)
{
	if (philo->vars->count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		log_status(philo, "has taken a fork");
		ft_sleep(philo->tt_die);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (!take_forks(philo))
		return (0);
	log_status(philo, "is eating");
	philo->last_meal = get_time_ms();
	ft_sleep(philo->tt_eat);
	unlock_forks(philo);
	return (op_arg(philo));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->id * 500);
	while (!is_dead(philo))
	{
		if (!eat_routine(philo) || is_dead(philo))
			break ;
		log_status(philo, "is sleeping");
		ft_sleep(philo->tt_sleep);
		if (is_dead(philo))
			break ;
		log_status(philo, "is thinking");
	}
	return (NULL);
}
