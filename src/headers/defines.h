/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:09 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 19:08:16 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "includes.h"

/* PROGRAM ARGUMENTS */
# define EXPECTED_AC					8
# define NUMBER_OF_CODERS				"--number_of_coders"
# define TIME_TO_BURNOUT				"--time_to_burnout"
# define TIME_TO_COMPILE				"--time_to_compile"
# define TIME_TO_DEBUG					"--time_to_debug"
# define TIME_TO_REFACTOR				"--time_to_refactor"
# define NUMBER_OF_COMPILES_REQUIRED	"--number_of_compiles_required"
# define DONGLE_COOLDOWN				"--dongle_cooldown"
# define SCHEDULER						"--scheduler"

# ifndef LOG_LEVEL
#  define LOG_LEVEL 1 /* INFO */
# endif

/* EXIT STATUSES */
# define SUCCESS 0
# define FAILURE 1

typedef enum e_log_level
{
	DEBUG = 0,
	INFO = 1,
	WARN = 2,
	ERROR = 3
}	t_log_level;

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
