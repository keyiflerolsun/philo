/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_semaphore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:12:22 by osancak           #+#    #+#             */
/*   Updated: 2025/07/25 12:59:51 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>   // * pthread_*
#include <semaphore.h> // * sem_*
#include <stdio.h>     // * printf
#include <unistd.h>    // * sleep

typedef struct s_kurek
{
	pthread_t	id;
	void		*res;
}				t_kurek;

typedef struct s_vars
{
	int			counter;
	sem_t		sem;
}				t_vars;

void	*bidi(void *args)
{
	t_vars	*vars;
	int		i;

	i = 0;
	vars = args;
	while (i++ < 10)
	{
		sem_wait(&vars->sem);
		printf("Thread %lu giriyor\n", pthread_self());
		(vars->counter)++;
		sleep(1);
		printf("Thread %lu çıkıyor\n", pthread_self());
		sem_post(&vars->sem);
	}
	return (&vars->counter);
}

int	main(void)
{
	t_kurek	kurek1;
	t_kurek	kurek2;
	t_vars	vars;

	vars.counter = 0;
	sem_init(&vars.sem, 0, 2);  // 0=başka process kullanmayacak - 2 thread aynı anda girebilir

	pthread_create(&kurek1.id, NULL, bidi, &vars);
	pthread_create(&kurek2.id, NULL, bidi, &vars);

	pthread_join(kurek1.id, &kurek1.res);
	printf("Thread 1 : %d\n", *(int *)kurek1.res);

	pthread_join(kurek2.id, &kurek2.res);
	printf("Thread 2 : %d\n", *(int *)kurek2.res);

	printf("Sonuç    : %d\n", vars.counter);

	sem_destroy(&vars.sem);
	return (0);
}

