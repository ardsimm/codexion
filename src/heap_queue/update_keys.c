/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:58:12 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:15:36 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "heap_queue/headers/heap_queue_lib.h"

void	hq_update_keys(t_heap_queue *hq)
{
	size_t	i;

	i = 0;
	while (i < hq->size)
	{
		hq->data[i].key = hq->update_key(&hq->data[i]);
		i++;
	}
	i = hq->size / 2;
	while (i-- > 0)
		heap_queue_align_down(hq, i);
}
