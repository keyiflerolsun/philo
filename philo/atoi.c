/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:16:01 by osancak           #+#    #+#             */
/*   Updated: 2025/07/29 11:17:09 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_possible(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	ft_atoi(const char *nptr, int *res)
{
	long int	toi;
	int			sig;

	sig = 1;
	toi = 0;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sig *= -1;
	if (!is_possible(nptr))
		return (0);
	while (*nptr && ft_isdigit(*nptr))
	{
		toi = toi * 10;
		if (toi >= 2147483647)
			return (0);
		toi += (*nptr++ - '0');
	}
	if (toi * sig > 2147483647 || toi * sig < -2147483648)
		return (0);
	*res = toi * sig;
	return (1);
}
