/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:11:40 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 17:33:06 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	hq_mutex_add(t_heap_queue_mutex *hq_mutex, void *value)
{
	pthread_mutex_lock(&hq_mutex->mutex);
	hq_add(hq_mutex->data, value);
	pthread_mutex_unlock(&hq_mutex->mutex);
}

void	*hq_mutex_pop(t_heap_queue_mutex *hq_mutex)
{
	void	*item;

	pthread_mutex_lock(&hq_mutex->mutex);
	item = hq_pop(hq_mutex->data);
	pthread_mutex_unlock(&hq_mutex->mutex);
	return (item);
}

size_t	hq_mutex_get_size(t_heap_queue_mutex *hq_mutex)
{
	size_t	size;

	pthread_mutex_lock(&hq_mutex->mutex);
	size = hq_mutex->data->size;
	pthread_mutex_unlock(&hq_mutex->mutex);
	return (size);
}

bool	hq_mutex_compare_coder_id(t_heap_queue_mutex *hq_mutex, size_t id)
{
	bool	equals;

	pthread_mutex_lock(&hq_mutex->mutex);
	equals = hq_mutex->data->size
		&& ((t_coder *)hq_mutex->data->data[0].data)->id == id;
	pthread_mutex_unlock(&hq_mutex->mutex);
	return (equals);
}

bool	hq_mutex_contains(t_heap_queue_mutex *hq_mutex, void *data)
{
	size_t	i;

	i = 0;
	pthread_mutex_lock(&hq_mutex->mutex);
	while (i < hq_mutex->data->size)
		if (hq_mutex->data->data[i++].data == data)
			return (true);
	pthread_mutex_unlock(&hq_mutex->mutex);
	return (false);
}

bool	hq_mutex_coder_is_next(t_heap_queue_mutex *hq_mutex, t_coder *coder)
{
	bool	result;

	pthread_mutex_lock(&hq_mutex->mutex);
	result = ((t_coder *)hq_mutex->data->data[0].data)->id == coder->id;
	pthread_mutex_unlock(&hq_mutex->mutex);
	return (result);
}
