/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:50:32 by smenard           #+#    #+#             */
/*   Updated: 2026/05/13 11:46:56 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static bool	validate_scheduler(char *value)
{
	return (
		value != NULL
		&& (
			!strcmp(value, "EDF")
			|| !strcmp(value, "FIFO")
		)
	);
}

static bool	validate_int_value(int value)
{
	return (value >= 0);
}

bool	validate_simulation(t_simulation *sim)
{
	bool	valid;

	valid = true;
	valid &= validate_int_value(sim->coders_count);
	valid &= validate_int_value(sim->time_to_burnout);
	valid &= validate_int_value(sim->time_to_compile);
	valid &= validate_int_value(sim->time_to_debug);
	valid &= validate_int_value(sim->time_to_refactor);
	valid &= validate_int_value(sim->number_of_compiles);
	valid &= validate_int_value(sim->dongle_cooldown);
	valid &= validate_scheduler(sim->scheduler);
	return (valid);
}
