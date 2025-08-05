#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int	main(void)
{
	struct timespec start, end;

	long	stack_time;
	long	heap_time;
	int		i;

	i = 0;
	while (++i)
	{
		// Stack tahsisi
		clock_gettime(CLOCK_MONOTONIC, &start);
		int stack_array[100000]; // Stack üzerinden tahsis
		clock_gettime(CLOCK_MONOTONIC, &end);
		stack_time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

		// Heap tahsisi
		clock_gettime(CLOCK_MONOTONIC, &start);
		int *heap_array = malloc((100000 * i) * sizeof(int)); // Heap üzerinden tahsis
		clock_gettime(CLOCK_MONOTONIC, &end);
		heap_time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

		printf("Stack tahsis süresi : %ld mikrosaniye\n", stack_time);
		printf("Heap tahsis süresi  : %ld mikrosaniye\n\n\n", heap_time);

		free(heap_array);

		sleep(1);
	}
	return (0);
}
