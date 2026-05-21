/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:59:08 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 16:59:20 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

t_heap_queue	*hq_init(size_t initial_size, size_t el_size,
		size_t (*get_key)(void *el),
		size_t (*update_key)(t_heap_queue_item *item))
{
	t_heap_queue	*hq;

	hq = ft_calloc(1, sizeof(t_heap_queue));
	if (!hq)
		return (NULL);
	hq->max_size = initial_size;
	hq->size = 0;
	hq->data = ft_calloc(initial_size, el_size);
	hq->get_key = get_key;
	hq->update_key = update_key;
	return (hq);
}
