/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:03:22 by osancak           #+#    #+#             */
/*   Updated: 2025/07/28 15:23:53 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>  // * pthread_*
# include <stdio.h>    // * printf
# include <stdlib.h>   // * malloc, free
# include <string.h>   // * memset
# include <sys/time.h> // * gettimeofday
# include <unistd.h>   // * write, usleep

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			start_time;
	long			last_meal;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_vars	*vars;
}					t_philo;

typedef struct s_vars
{
	t_philo			*philos;
	int				count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_t		alive;
	int				all_is_well;
}					t_vars;

int					ft_atoi(const char *nptr);
long				get_time_ms(void);
void				log_status(t_philo *philo, char *msg);
int					init_prog(t_vars *vars, char **argv);
void				run_threads(t_vars *vars);
void				*routine(void *arg);
void				*check_alive(void *args);

#endif
