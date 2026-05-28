/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue_lib.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:56:55 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 16:59:45 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_QUEUE_LIB_H
# define HEAP_QUEUE_LIB_H

# include "headers/defines.h"

/* align.c */
void			heap_queue_align_up(t_heap_queue *hq, int idx);
void			heap_queue_align_down(t_heap_queue *hq, size_t idx);

/* init.c */

t_heap_queue	*hq_init(size_t initial_size, size_t el_size,
					size_t (*get_key)(void *el));

#endif
