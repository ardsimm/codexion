/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedulers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:22:23 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:10:56 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

size_t	get_key_fifo(void *el)
{
	t_heap_queue_item	*item;

	item = (t_heap_queue_item *)el;
	if (item->key)
		return (item->key);
	return (get_time_us());
}

size_t	update_key_fifo(t_heap_queue_item *item)
{
	return (item->key);
}
