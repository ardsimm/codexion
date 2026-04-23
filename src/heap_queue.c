/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:32:39 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 15:01:44 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_heap_queue	*heap_queue_create(size_t initial_size, size_t el_size)
{
	(void) initial_size;
	(void) el_size;
	return (NULL);
}

void	heap_queue_add(t_heap_queue *queue, void *data)
{
	(void) queue;
	(void) data;
}

void	*heap_queue_remove(t_heap_queue *queue, void *data)
{
	(void) queue;
	(void) data;
	return (NULL);
}

void	*heap_queue_pop(t_heap_queue *queue)
{
	(void) queue;
	return (NULL);
}

void	*heap_queue_clear(t_heap_queue *queue)
{
	(void) queue;
	return (EXIT_SUCCESS);
}
