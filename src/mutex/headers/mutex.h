/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:16:57 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:46:35 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include "headers/defines.h"

/* getters.c */
size_t			get_size_t_mutex(t_size_t_mutex *mutex);

t_typed_voidp	get_voidp_mutex(t_voidp_mutex *mutex);

bool			get_bool_mutex(t_bool_mutex *mutex);

void			set_voidp_mutex(t_voidp_mutex *mutex, t_typed_voidp data);

/* setters.c */
void			set_size_t_mutex(t_size_t_mutex *mutex, size_t data);

void			set_bool_mutex(t_bool_mutex *mutex, bool data);

void			set_heap_queue_mutex(t_heap_queue_mutex *mutex,
					t_heap_queue *value);

/* init.c */
void			init_voidp_mutex(t_voidp_mutex *mutex, t_typed_voidp value);

void			init_size_t_mutex(t_size_t_mutex *mutex, size_t value);

void			init_bool_mutex(t_bool_mutex *mutex, bool value);

void			init_heap_queue_mutex(t_heap_queue_mutex *mutex,
					t_heap_queue *value);

/* heap_queue.c */

void			hq_mutex_add(t_heap_queue_mutex *hq_mutex, void *value);

void			*hq_mutex_pop(t_heap_queue_mutex *hq_mutex);

size_t			hq_mutex_get_size(t_heap_queue_mutex *hq_mutex);

bool			hq_mutex_compare_coder_id(t_heap_queue_mutex *hq_mutex,
					size_t id);

bool			hq_mutex_contains(t_heap_queue_mutex *hq_mutex, void *data);

bool			hq_mutex_coder_is_next(t_heap_queue_mutex *hq_mutex,
					t_coder *coder);

#endif
