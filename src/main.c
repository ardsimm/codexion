/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/04/29 15:20:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	main(int ac, char **av)
{
	t_simulation	*simulation;

	simulation = parse(ac, av);
	if (!simulation)
	{
		printf("ERROR\n");
		return (EXIT_FAILURE);
	}
	else
	{
		printf("PARSE RESULT:\n");
		printf("coders_count: %d\n", simulation->coders_count);
		printf("time_to_burnout: %d\n", simulation->time_to_burnout);
		printf("time_to_compile: %d\n", simulation->time_to_compile);
		printf("time_to_debug: %d\n", simulation->time_to_debug);
		printf("time_to_refactor: %d\n", simulation->time_to_refactor);
		printf("number_of_compiles: %d\n", simulation->number_of_compiles);
		printf("dongle_cooldown: %d\n", simulation->dongle_cooldown);
		printf("scheduler: %s\n", simulation->scheduler);
	}
	free_return((void *[]){simulation->scheduler, simulation}, 2,
		(void *)EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
