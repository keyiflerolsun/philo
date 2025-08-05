/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:29:34 by osancak           #+#    #+#             */
/*   Updated: 2025/08/05 16:16:44 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_op(t_philo *philo)
{
	if (philo->vars->op_arg)
	{
		pthread_mutex_lock(&philo->vars->death_mutex);
		if (!philo->must_eat)
		{
			pthread_mutex_unlock(&philo->vars->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->vars->death_mutex);
	}
	return (1);
}

static int	check_well(t_vars *vars, t_philo *philo)
{
	pthread_mutex_lock(&vars->death_mutex);
	if (get_time_ms() - philo->last_meal > philo->tt_die)
	{
		vars->all_is_well = 0;
		pthread_mutex_unlock(&vars->death_mutex);
		log_status(philo, "died");
		return (0);
	}
	pthread_mutex_unlock(&vars->death_mutex);
	return (1);
}

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
			if (!check_op(philo) || !check_well(vars, philo))
				return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}
