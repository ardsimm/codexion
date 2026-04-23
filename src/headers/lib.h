/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:25 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 14:39:12 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "headers/includes.h"

/* logging.c */
void			*log(char *str);

/* routine.c */
void			*coder_routine(void *data);

/* simulation.c */
void			*run_simulation(t_simulation *simulation);

/* heap_queue.c */
t_heap_queue	*heap_queue_create(size_t initial_size);
void			heap_queue_add(t_heap_queue *queue, void *data);
void			*heap_queue_remove(t_heap_queue *queue, void *data);
void			*heap_queue_remove_idx(t_heap_queue *queue, size_t idx);
void			*heap_queue_pop(t_heap_queue *queue);
void			*heap_queue_clear(t_heap_queue *queue);

#endif