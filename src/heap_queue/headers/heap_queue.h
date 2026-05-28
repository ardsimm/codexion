/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:53:00 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 16:25:46 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_QUEUE_H
# define HEAP_QUEUE_H

# include "headers/defines.h"

t_heap_queue	*hq_init(size_t initial_size, size_t el_size,
					size_t (*get_key)(void *el));

void			hq_add(t_heap_queue *hq, void *data);

void			*hq_pop(t_heap_queue *hq);

void			hq_update_keys(t_heap_queue *hq);

void			hq_free(t_heap_queue *hq);

bool			hq_contains(t_heap_queue *hq, void *data);

#endif
