/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:32:39 by smenard           #+#    #+#             */
/*   Updated: 2026/05/11 14:51:09 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	heap_queue_align_up(t_heap_queue *hq, int idx)
{
	void	*temp;

	if (idx && hq->get_score(hq->data[(idx - 1)
			/ 2]) > hq->get_score(hq->data[idx]))
	{
		temp = hq->data[idx];
		hq->data[idx] = hq->data[(idx - 1) / 2];
		hq->data[(idx - 1) / 2] = temp;
		heap_queue_align_up(hq, (idx - 1) / 2);
	}
}

static void	heap_queue_align_down(t_heap_queue *hq, size_t idx)
{
	void	*temp;
	size_t	smallest;
	size_t	right;
	size_t	left;

	if (idx >= hq->size)
		return ;
	smallest = idx;
	right = 2 * idx + 1;
	left = 2 * idx + 2;
	if (right < hq->size
		&& hq->get_score(hq->data[right]) < hq->get_score(hq->data[smallest]))
		smallest = right;
	if (left < hq->size
		&& hq->get_score(hq->data[left]) < hq->get_score(hq->data[smallest]))
		smallest = left;
	if (smallest != idx)
	{
		temp = hq->data[idx];
		hq->data[idx] = hq->data[smallest];
		hq->data[smallest] = temp;
		heap_queue_align_down(hq, smallest);
	}
}

t_heap_queue	*heap_queue_init(size_t initial_size, size_t el_size,
		int (*get_score)(void *el))
{
	t_heap_queue	*hq;

	hq = ft_calloc(1, sizeof(t_heap_queue));
	hq->max_size = initial_size;
	hq->size = 0;
	hq->data = ft_calloc(initial_size, el_size);
	hq->get_score =  get_score;
	return (hq);
}

void	heap_queue_add(t_heap_queue *hq, void *data)
{
	if (hq->size >= hq->max_size)
		return ;
	hq->data[hq->size++] = data;
	heap_queue_align_up(hq, hq->size - 1);
}

void	*heap_queue_pop(t_heap_queue *hq)
{
	void	*item;

	if (!hq->size)
		return (NULL);
	item = hq->data[0];
	hq->data[0] = hq->data[--hq->size];
	heap_queue_align_down(hq, 0);
	return (item);
}
