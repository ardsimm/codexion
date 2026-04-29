/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/04/29 17:52:54 by smenard          ###   ########.fr       */
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
	else
	{
		ft_log_debug(sim, "Parsing successful", NULL);
		printf("PARSE RESULT:\n");
		printf("coders_count: %d\n", sim->coders_count);
		printf("time_to_burnout: %d\n", sim->time_to_burnout);
		printf("time_to_compile: %d\n", sim->time_to_compile);
		printf("time_to_debug: %d\n", sim->time_to_debug);
		printf("time_to_refactor: %d\n", sim->time_to_refactor);
		printf("number_of_compiles: %d\n", sim->number_of_compiles);
		printf("dongle_cooldown: %d\n", sim->dongle_cooldown);
		printf("scheduler: %s\n", sim->scheduler);
	}
	free_all((void *[]){sim->scheduler, sim->dongles, sim->coders, sim}, 4);
	return (EXIT_SUCCESS);
}
