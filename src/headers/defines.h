/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:09 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 14:50:11 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "includes.h"

typedef struct s_heap_queue
{
	size_t	size;
	void	*data;
}	t_heap_queue;

typedef enum e_scheduler_mode
{
	FIFO,
	EDF
}	t_scheduler_mode;

typedef struct s_dongle
{
	size_t				id;
	t_heap_queue		*queue;
	pthread_mutex_t		mutex;
	t_scheduler_mode	scheduler_mode;
	size_t				cooldown;
	size_t				last_use_timestamp;
}	t_dongle;

typedef struct s_coder
{
	size_t				id;
	size_t				last_task_end_timestamp;
	size_t				compilation_count;
	size_t				time_to_burnout;
	size_t				time_to_compile;
	size_t				time_to_debug;
	size_t				time_to_refactor;
}	t_coder;

/**
 * Simulation parameters
 * - {coders_count}: Number of coders in the simulation
 *
 * - {dongles}: The dongles of the simulation
 *
 * - {coders}: The coders of the simulation
 *
 * - {time_to_burnout}: Time until the coders burnout
 *   (from the beggining of the simulation OR the end of their last compilation)
 *
 * - {time_to_compile}: Time required by the coders for the compile task
 *
 * - {time_to_debug}: Time required by the coders for the debug task
 *
 * - {time_to_refactor}: Time required by the coders for the refactor task
 *
 * - {number of compiles}: The number of compilation cycles
 *   required to finish the simulation
 *
 * - {dongle_cooldown}: The timeout before a dongle can be used again
 *   after being released by a coder
 *
 * - {logging_mutex}: Global mutex for thread-safe logging
 */
typedef struct s_simulation
{
	size_t				coders_count;
	t_dongle			*dongles;
	t_coder				*coders;
	size_t				time_to_burnout;
	size_t				time_to_compile;
	size_t				time_to_debug;
	size_t				time_to_refactor;
	size_t				number_of_compiles;
	size_t				dongle_cooldown;
	pthread_mutex_t		logging_mutex;
}	t_simulation;

#endif
