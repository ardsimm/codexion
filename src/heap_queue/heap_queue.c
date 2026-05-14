/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:32:39 by smenard           #+#    #+#             */
/*   Updated: 2026/05/14 15:32:27 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static void	heap_queue_align_up(t_heap_queue *hq, int idx)
{
	t_heap_queue_item	temp;

	if (idx && hq->data[(idx - 1) / 2].key > hq->data[idx].key)
	{
		temp = hq->data[idx];
		hq->data[idx] = hq->data[(idx - 1) / 2];
		hq->data[(idx - 1) / 2] = temp;
		heap_queue_align_up(hq, (idx - 1) / 2);
	}
}

static void	heap_queue_align_down(t_heap_queue *hq, size_t idx)
{
	t_heap_queue_item	temp;
	size_t				smallest;
	size_t				right;
	size_t				left;

	if (idx >= hq->size)
		return ;
	smallest = idx;
	right = 2 * idx + 1;
	left = 2 * idx + 2;
	if (right < hq->size && hq->data[right].key < hq->data[smallest].key)
		smallest = right;
	if (left < hq->size && hq->data[left].key < hq->data[smallest].key)
		smallest = left;
	if (smallest != idx)
	{
		temp = hq->data[idx];
		hq->data[idx] = hq->data[smallest];
		hq->data[smallest] = temp;
		heap_queue_align_down(hq, smallest);
	}
}

t_heap_queue	*hq_init(size_t initial_size, size_t el_size,
		size_t (*get_key)(t_shared_ctx *ctx, void *el))
{
	t_heap_queue	*hq;

	hq = ft_calloc(1, sizeof(t_heap_queue));
	hq->max_size = initial_size;
	hq->size = 0;
	hq->data = ft_calloc(initial_size, el_size);
	hq->get_key = get_key;
	return (hq);
}

void	hq_add(t_heap_queue *hq, t_shared_ctx *ctx, void *data)
{
	if (hq->size >= hq->max_size)
		return ;
	hq->data[hq->size++] = (t_heap_queue_item){.key = hq->get_key(ctx, data),
		.data = data};
	heap_queue_align_up(hq, hq->size - 1);
}

void	*hq_pop(t_heap_queue *hq)
{
	t_heap_queue_item	*item;

	if (!hq->size)
		return (NULL);
	item = &hq->data[0];
	hq->data[0] = hq->data[--hq->size];
	heap_queue_align_down(hq, 0);
	return (item->data);
}
