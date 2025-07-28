/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:04:55 by osancak           #+#    #+#             */
/*   Updated: 2025/07/25 13:00:07 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> // * pthread_*
#include <stdio.h>   // * printf
#include <unistd.h>  // * sleep

typedef struct s_kurek
{
	pthread_t		id;
	void			*res;
}					t_kurek;

typedef struct s_vars
{
	int				counter;
	pthread_mutex_t	mutex;
}					t_vars;

void	*bidi(void *args)
{
	t_vars	*vars;
	int		i;

	i = 0;
	vars = args;
	while (i++ < 10)
	{
		pthread_mutex_lock(&vars->mutex);
		printf("Thread %lu giriyor\n", pthread_self());
		(vars->counter)++;
		sleep(1);
		printf("Thread %lu çıkıyor\n", pthread_self());
		pthread_mutex_unlock(&vars->mutex);
	}
	return (&vars->counter);
}

int	main(void)
{
	t_kurek	kurek1;
	t_kurek	kurek2;
	t_vars	vars;

	vars.counter = 0;
	pthread_mutex_init(&vars.mutex, NULL);

	pthread_create(&kurek1.id, NULL, bidi, &vars);
	pthread_create(&kurek2.id, NULL, bidi, &vars);

	pthread_join(kurek1.id, &kurek1.res);
	printf("Thread 1 : %d\n", *(int *)kurek1.res);

	pthread_join(kurek2.id, &kurek2.res);
	printf("Thread 2 : %d\n", *(int *)kurek2.res);

	printf("Sonuç    : %d\n", vars.counter);

	pthread_mutex_destroy(&vars.mutex);
	return (0);
}
