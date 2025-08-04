/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:57:29 by osancak           #+#    #+#             */
/*   Updated: 2025/08/04 17:15:30 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_vars *vars)
{
	int	i;

	vars->philos = malloc(sizeof(t_philo) * vars->count);
	if (!vars->philos)
		return (0);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->count);
	if (!vars->forks)
		return (0);
	vars->all_is_well = 1;
	pthread_mutex_init(&vars->print_mutex, NULL);
	pthread_mutex_init(&vars->death_mutex, NULL);
	i = -1;
	while (++i < vars->count)
		pthread_mutex_init(&vars->forks[i], NULL);
	return (1);
}

int	init_prog(t_vars *vars, char **argv)
{
	int		i;
	long	start_time;

	if (!init_mutex(vars))
		return (0);
	start_time = get_time_ms();
	i = -1;
	while (++i < vars->count)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].start_time = start_time;
		vars->philos[i].last_meal = start_time;
		ft_atoi(argv[2], &vars->philos[i].tt_die);
		ft_atoi(argv[3], &vars->philos[i].tt_eat);
		ft_atoi(argv[4], &vars->philos[i].tt_sleep);
		vars->philos[i].left_fork = &vars->forks[i];
		vars->philos[i].right_fork = &vars->forks[(i + 1) % vars->count];
		vars->philos[i].vars = vars;
		if (vars->op_arg)
			ft_atoi(argv[5], &vars->philos[i].must_eat);
		else
			vars->philos[i].must_eat = 0;
	}
	return (1);
}

void	run_threads(t_vars *vars)
{
	int		i;
	t_philo	*philos;

	philos = vars->philos;
	i = -1;
	while (++i < vars->count)
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	pthread_create(&vars->alive, NULL, check_alive, vars);
	i = -1;
	while (++i < vars->count)
		pthread_join(philos[i].thread, NULL);
	pthread_join(vars->alive, NULL);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}
