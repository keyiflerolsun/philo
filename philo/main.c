/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:48:29 by osancak           #+#    #+#             */
/*   Updated: 2025/07/28 13:05:34 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5)
	{
		printf("./philo count tt_die tt_eat tt_sleep\n");
		return (1);
	}
	vars.count = ft_atoi(argv[1]);
	if (vars.count <= 0)
		return (1);
	if (!init_prog(&vars, argv))
		return (1);
	run_threads(&vars);
	free(vars.philos);
	free(vars.forks);
	return (0);
}
