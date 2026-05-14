/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:09 by smenard           #+#    #+#             */
/*   Updated: 2026/05/14 15:34:07 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "headers/includes.h"

/* PROGRAM ARGUMENTS */
# define EXPECTED_AC 9

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
}							t_log_level;

typedef struct s_heap_queue_item
{
	size_t					key;
	void					*data;
}							t_heap_queue_item;

typedef struct s_shared_ctx
{
	uint32_t				time_to_burnout;
	uint32_t				time_to_compile;
	uint32_t				time_to_debug;
	uint32_t				time_to_refactor;
	uint32_t				number_of_compiles;
	uint32_t				dongle_cooldown;
	pthread_mutex_t			logging_mutex;
	size_t					timestamp_start;
	struct timeval			tv;
}							t_shared_ctx;

typedef struct s_heap_queue
{
	size_t					size;
	size_t					max_size;
	t_heap_queue_item		*data;
	size_t					(*get_key)(t_shared_ctx *ctx, void *el);
}							t_heap_queue;

typedef enum e_scheduler_mode
{
	FIFO,
	EDF
}							t_scheduler_mode;

typedef enum e_data_type
{
	INT,
	STR
}							t_data_type;

typedef struct e_typed_voidp
{
	t_data_type				type;
	void					*data;
}							t_typed_voidp;

typedef struct s_dongle
{
	size_t					id;
	t_heap_queue			*hq;
	size_t					cooldown;
	size_t					last_use_timestamp;
	pthread_mutex_t			in_use_mutex;
	bool					in_use;
}							t_dongle;

typedef struct s_coder
{
	size_t					id;
	size_t					last_task_end_timestamp;
	size_t					compilation_count;
	bool					done;
	t_dongle				*dongle_left;
	t_dongle				*dongle_right;
	t_shared_ctx			shared;
}							t_coder;

/**
 * Simulation parameters
 * - {coders_count}: Number of coders in the simulation
 *
 * - {dongles}: The dongles of the simulation
 *
 * - {coders}: The coders of the simulation
 *
 * - {shared}: Shared context between monitor and coders
 *   Content:
 *   - {time_to_burnout}: Time until the coders burnout
 *     from the beggining of the simulation
 *     or the start of their last compilation
 *
 *   - {time_to_compile}: Time required by the coders for the compile task
 *
 *   - {time_to_debug}: Time required by the coders for the debug task
 *
 *   - {time_to_refactor}: Time required by the coders for the refactor task
 *
 *   - {number of compiles}: The number of compilation cycles
 *     required to finish the simulation
 *
 *   - {dongle_cooldown}: The timeout before a dongle can be used again
 *     after being released by a coder
 *
 *   - {logging_mutex}: Global mutex for thread-safe logging
 */
typedef struct s_ctx
{
	uint32_t				coders_count;
	t_dongle				*dongles;
	t_coder					*coders;
	char					*scheduler;
	t_shared_ctx			shared;
}							t_ctx;

#endif