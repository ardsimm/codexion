/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/04/27 17:28:25 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	main(int ac, char **av)
{
	t_simulation	*sim;

	sim = parse(ac, av);
	printf("ac: %d \n", ac);
	if (!sim)
		printf("ERROR\n");
	else
	{
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
	return (EXIT_SUCCESS);
}
