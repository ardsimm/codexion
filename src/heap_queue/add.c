/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:59:59 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:00:25 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "heap_queue/headers/heap_queue_lib.h"

void	hq_add(t_heap_queue *hq, void *data)
{
	if (hq->size >= hq->max_size)
		return ;
	hq->data[hq->size++] = (t_heap_queue_item){.key = hq->get_key(data),
		.data = data};
	heap_queue_align_up(hq, hq->size - 1);
}
