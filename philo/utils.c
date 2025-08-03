/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 09:11:18 by osancak           #+#    #+#             */
/*   Updated: 2025/08/03 18:31:45 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

int	is_dead(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->vars->death_mutex);
	res = !philo->vars->all_is_well;
	pthread_mutex_unlock(&philo->vars->death_mutex);
	return (res);
}

void	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (!is_dead(philo))
		log_status(philo, "has taken a fork");
}

int	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	log_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %d %s\n", get_time_ms() - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}
