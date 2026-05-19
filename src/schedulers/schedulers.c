/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedulers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:22:23 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 15:22:34 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

size_t	get_key_fifo(void *el)
{
	struct timeval		tv;
	t_heap_queue_item	*item;

	item = (t_heap_queue_item *)el;
	if (item->key)
		return (item->key);
	gettimeofday(&tv, NULL);
	return (tv.tv_sec);
}

size_t	update_key_fifo(t_heap_queue_item *item)
{
	return (item->key);
}
