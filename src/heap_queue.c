/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:32:39 by smenard           #+#    #+#             */
/*   Updated: 2026/05/05 16:30:39 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	heap_queue_align_up(t_heap_queue *hq, int idx)
{
	void	*temp;

	if (
		idx
		&& hq->get_score(hq->data[(idx - 1) / 2]) > hq->get_score(hq->data[idx])
	)
	{
		temp = hq->data[idx];
		hq->data[idx] = hq->data[(idx - 1) / 2];
		hq->data[(idx - 1) / 2] = temp;
		heap_queue_align(hq, (idx - 1) / 2);
	}
}

static void heap_queue_align_down(t_heap_queue *hq, int idx)
{
	int	smallest;
	int	right;
	int	left;

	smallest = idx;
	right = 2 * idx + 1;
	left = 2 * idx + 2;

}


t_heap_queue	*heap_queue_init(size_t initial_size, size_t el_size)
{
	t_heap_queue	*hq;

	hq = ft_calloc(1, sizeof(t_heap_queue));
	hq->max_size = initial_size;
	hq->size = 0;
	hq->data = ft_calloc(initial_size, el_size);
	return (hq);
}

void	heap_queue_add(t_heap_queue *hq, void *data)
{
	if (hq->size >= hq->max_size)
		return ;
	hq->data[hq->size++] = data;
	heap_queue_align(hq, hq->size - 1);
}

void	*heap_queue_pop(t_heap_queue *hq)
{
	(void) hq;
	return (NULL);
}

void	*heap_queue_peek(t_heap_queue *hq)
{
	if (!hq->size)
		return (NULL);
	return (hq->data[0]);
}

void	heap_queue_clear(t_heap_queue *hq)
{
	free(hq->data);
	free(hq);
}
