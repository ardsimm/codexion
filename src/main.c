/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/05/12 17:14:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	get_score(void *el);

static void	init_coder(uint32_t i, t_simulation *sim)
{
	size_t	dongle_left_idx;
	size_t	dongle_right_idx;

	dongle_left_idx = i - 1;
	if (i < 0)
		dongle_left_idx = sim->coders_count - 1;
	dongle_right_idx = i + 1;
	if (dongle_right_idx > sim->coders_count - 1)
		dongle_left_idx = 0;
	sim->coders[i].id = i;
	sim->coders[i].time_to_burnout = sim->time_to_burnout;
	sim->coders[i].time_to_compile = sim->time_to_compile;
	sim->coders[i].time_to_debug = sim->time_to_debug;
	sim->coders[i].time_to_refactor = sim->time_to_refactor;
	sim->coders[i].time_to_refactor = sim->time_to_refactor;
	sim->coders[i].logging_mutex = &sim->logging_mutex;
	sim->coders[i].logging_blocked = &sim->logging_blocked;
	sim->coders[i].dongle_left = &sim->dongles[dongle_left_idx];
	sim->coders[i].dongle_right = &sim->dongles[dongle_right_idx];
}

static void	init_dongle(uint32_t i, t_simulation *sim)
{
	sim->dongles[i].id = i;
	sim->dongles[i].queue = heap_queue_init(2, sizeof(t_coder), get_score);
	pthread_mutex_init(&sim->dongles[i].in_use_mutex, NULL);
	sim->dongles[i].cooldown = sim->dongle_cooldown;
}

static int	init(t_simulation *sim)
{
	uint32_t	i;

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
		ft_log_error(NULL, "Parsing error", NULL);
		return (FAILURE);
	}
	if (init(sim) == FAILURE)
	{
		ft_log_error(NULL, "Initialization error", NULL);
		return ((int)free_return_int((void *[]){sim->scheduler, sim}, 2,
			EXIT_FAILURE));
	}
	ft_log_debug(NULL, "Parsing successful", NULL);
	monitor_simulation(sim);
	free_all((void *[]){sim->scheduler, sim->dongles, sim->coders, sim}, 4);
	return (EXIT_SUCCESS);
}
