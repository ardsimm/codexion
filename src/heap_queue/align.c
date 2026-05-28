/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:55:18 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 16:55:31 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	heap_queue_align_up(t_heap_queue *hq, int idx)
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

void	heap_queue_align_down(t_heap_queue *hq, size_t idx)
{
	t_heap_queue_item	temp;
	size_t				smallest;
	size_t				right;
	size_t				left;

	if (idx >= hq->size)
		return ;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;
	if (left < hq->size && hq->data[left].key < hq->data[smallest].key)
		smallest = left;
	if (right < hq->size && hq->data[right].key < hq->data[smallest].key)
		smallest = right;
	if (smallest != idx)
	{
		temp = hq->data[idx];
		hq->data[idx] = hq->data[smallest];
		hq->data[smallest] = temp;
		heap_queue_align_down(hq, smallest);
	}
}
