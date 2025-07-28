/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osancak <osancak@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:07:29 by osancak           #+#    #+#             */
/*   Updated: 2025/07/25 13:00:03 by osancak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> // * pthread_*
#include <stdio.h>   // * printf

typedef struct s_kurek
{
	pthread_t		id;
	void			*res;
}					t_kurek;

void	*bidi(void *counter)
{
	int		i;

	i = 0;
	while (i++ < 100000)
		(*(int *)counter)++;
	return (counter);
}

int	main(void)
{
	t_kurek	kurek1;
	t_kurek	kurek2;
	int		counter;

	counter = 0;
	pthread_create(&kurek1.id, NULL, bidi, &counter);
	pthread_create(&kurek2.id, NULL, bidi, &counter);

	pthread_join(kurek1.id, &kurek1.res);
	printf("Thread 1 : %d\n", *(int *)kurek1.res);

	pthread_join(kurek2.id, &kurek2.res);
	printf("Thread 2 : %d\n", *(int *)kurek2.res);

	printf("Sonuç    : %d\n", counter);
	return (0);
}
