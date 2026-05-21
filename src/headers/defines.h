/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:09 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:29:49 by smenard          ###   ########.fr       */
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

typedef enum e_data_type
{
	INT,
	STR,
}							t_data_type;

typedef struct s_heap_queue
{
	size_t					size;
	size_t					max_size;
	t_heap_queue_item		*data;
	size_t					(*get_key)(void *el);
	size_t					(*update_key)(t_heap_queue_item *item);
}							t_heap_queue;

typedef struct e_typed_voidp
{
	t_data_type				type;
	void					*data;
}							t_typed_voidp;

typedef struct s_voidp_cond
{
	pthread_mutex_t			mutex;
	pthread_cond_t			cond;
	t_typed_voidp			value;
}							t_voidp_cond;

typedef struct s_int_cond
{
	pthread_mutex_t			mutex;
	pthread_cond_t			cond;
	int						value;
}							t_int_cond;

typedef struct s_voidp_mutex
{
	pthread_mutex_t			mutex;
	t_typed_voidp			data;
}							t_voidp_mutex;

typedef struct s_bool_mutex
{
	pthread_mutex_t			mutex;
	bool					data;
}							t_bool_mutex;

typedef struct s_size_t_mutex
{
	pthread_mutex_t			mutex;
	size_t					data;
}							t_size_t_mutex;

typedef struct s_heap_queue_mutex
{
	pthread_mutex_t			mutex;
	t_heap_queue			*data;
}							t_heap_queue_mutex;

typedef struct s_shared_ctx
{
	uint32_t				time_to_burnout;
	uint32_t				time_to_compile;
	uint32_t				time_to_debug;
	uint32_t				time_to_refactor;
	uint32_t				number_of_compiles;
	uint32_t				dongle_cooldown;
	t_bool_mutex			logging_active;
	size_t					timestamp_start;
	t_bool_mutex			run;
	t_int_cond				start_condition;
}							t_shared_ctx;

typedef enum e_scheduler_mode
{
	FIFO,
	EDF,
	INVALID
}							t_scheduler_mode;

typedef struct s_dongle
{
	size_t					id;
	t_heap_queue			*hq;
	size_t					cooldown;
	t_size_t_mutex			last_use_timestamp;
	t_bool_mutex			in_use;
}							t_dongle;

typedef struct s_coder
{
	size_t					id;
	t_size_t_mutex			last_compile_timestamp;
	t_bool_mutex			done;
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
	t_scheduler_mode		scheduler;
	t_shared_ctx			shared;
}							t_ctx;

#endif
