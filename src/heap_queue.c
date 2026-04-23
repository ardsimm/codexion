/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:32:39 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 14:37:56 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_heap_queue	*heap_queue_create(size_t initial_size)
{
	(void) initial_size;
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

void	*heap_queue_remove_idx(t_heap_queue *queue, size_t idx)
{
	(void) queue;
	(void) idx;
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