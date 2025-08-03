/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 08:48:29 by osancak           #+#    #+#             */
/*   Updated: 2025/08/03 15:35:09 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->count)
		pthread_mutex_destroy(&vars->forks[i]);
	pthread_mutex_destroy(&vars->print_mutex);
	pthread_mutex_destroy(&vars->death_mutex);
	free(vars->philos);
	free(vars->forks);
}

static int	check_args(int argc, char **argv)
{
	int	res;

	while (--argc > 0)
	{
		if (!ft_atoi(argv[argc], &res) || res <= 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if ((argc != 5 && argc != 6) || !check_args(argc, argv))
	{
		printf("./philo count tt_die tt_eat tt_sleep\n");
		return (1);
	}
	ft_atoi(argv[1], &vars.count);
	if (argc == 6)
		vars.op_arg = 1;
	else
		vars.op_arg = 0;
	if (!init_prog(&vars, argv))
		return (1);
	run_threads(&vars);
	clean(&vars);
	return (0);
}
