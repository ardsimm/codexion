/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/05/11 14:56:45 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	init_coder(int32_t i, t_simulation *sim)
{
	sim->coders[i].id = i;
	sim->coders[i].time_to_burnout = sim->time_to_burnout;
	sim->coders[i].time_to_compile = sim->time_to_compile;
	sim->coders[i].time_to_debug = sim->time_to_debug;
	sim->coders[i].time_to_refactor = sim->time_to_refactor;
	sim->coders[i].time_to_refactor = sim->time_to_refactor;
}

static void	init_dongle(int32_t i, t_simulation *sim)
{
	sim->dongles[i].id = i;
	sim->dongles[i].queue = NULL; // TODO: implement heap queue
	pthread_mutex_init(&sim->dongles[i].mutex, NULL);
	sim->dongles[i].cooldown = sim->dongle_cooldown;
	if (!strcmp(sim->scheduler, "FIFO"))
		sim->dongles[i].scheduler_mode = FIFO;
	else
		sim->dongles[i].scheduler_mode = EDF;
}

static int	init(t_simulation *sim)
{
	int32_t	i;

	i = 0;
	pthread_mutex_init(&sim->logging_mutex, NULL);
	sim->coders = ft_calloc(sim->coders_count, sizeof(t_coder));
	if (!sim->coders)
		return (FAILURE);
	while (i < sim->coders_count)
		init_coder(i++, sim);
	i = 0;
	sim->dongles = ft_calloc(sim->coders_count, sizeof(t_dongle));
	if (!sim->dongles)
		return (free_return_int((void *[]){sim->dongles}, 1,
			FAILURE));
	while (i < sim->coders_count)
		init_dongle(i++, sim);
	return (SUCCESS);
}

void	print_hq(t_heap_queue *hq)
{
	printf("Heap queue size: %zu	\n", hq->size);
	for (size_t i = 0; i < hq->size; i++)
		printf("hq[%zu]: %d\n", i, *(int*)hq->data[i]);
}

void test_hq(t_heap_queue *hq)
{
	int	n1 = 4;
	int	n2 = 3;
	int	n3 = 2;
	int n4 = 1;

	heap_queue_add(hq, &n3);
	heap_queue_add(hq, &n4);
	heap_queue_add(hq, &n1);
	heap_queue_add(hq, &n2);
	print_hq(hq);
	printf("Popping...\n");
	heap_queue_pop(hq);
	print_hq(hq);
	printf("Popping...\n");
	heap_queue_pop(hq);
	print_hq(hq);
	printf("Popping...\n");
	heap_queue_pop(hq);
	print_hq(hq);
	printf("Popping...\n");
	heap_queue_pop(hq);
	print_hq(hq);
}

int	get_score(void *el)
{
	return (*(int*)el);
}

int	main(int ac, char **av)
{
	t_simulation	*sim;

	sim = parse(ac, av);
	if (!sim)
	{
		ft_log_error(sim, "Parsing error", NULL);
		return (FAILURE);
	}
	if (init(sim) == FAILURE)
	{
		ft_log_error(sim, "Initialization error", NULL);
		return ((int)free_return_int((void *[]){sim->scheduler, sim}, 2,
			EXIT_FAILURE));
	}
	ft_log_debug(sim, "Parsing successful", NULL);
	test_hq(heap_queue_init(32, sizeof(int), get_score));
	free_all((void *[]){sim->scheduler, sim->dongles, sim->coders, sim}, 4);
	return (EXIT_SUCCESS);
}
