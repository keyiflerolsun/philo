/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 09:11:18 by osancak           #+#    #+#             */
/*   Updated: 2025/08/02 16:10:30 by osancak          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->vars->death_mutex);
	if (!philo->vars->all_is_well)
	{
		pthread_mutex_unlock(&philo->vars->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->death_mutex);
	return (0);
}

void	log_status(t_philo *philo, char *msg)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->start_time;
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}
