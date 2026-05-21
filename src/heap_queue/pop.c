/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:13:18 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:13:41 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "heap_queue/headers/heap_queue_lib.h"

void	*hq_pop(t_heap_queue *hq)
{
	void	*data;

	if (!hq->size)
		return (NULL);
	data = hq->data[0].data;
	hq->data[0] = hq->data[--hq->size];
	heap_queue_align_down(hq, 0);
	return (data);
}
