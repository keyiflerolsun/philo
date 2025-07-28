/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 09:11:18 by osancak           #+#    #+#             */
/*   Updated: 2025/07/28 15:22:57 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	long int	toi;
	int			sig;

	sig = 1;
	toi = 0;
	while (*nptr && ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' '))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sig *= -1;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		toi = toi * 10 + (*nptr++ - '0');
	if (toi * sig > 2147483647)
		return (-1);
	if (toi * sig < -2147483648)
		return (0);
	return (toi * sig);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

int	log_status(t_philo *philo, char *msg)
{
	long	timestamp;

	if (!philo->vars->all_is_well)
		return (0);
	timestamp = get_time_ms() - philo->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	return (1);
}
