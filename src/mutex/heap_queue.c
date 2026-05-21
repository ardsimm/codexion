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

void	hq_mutex_add(t_heap_queue_mutex *mutex, void *value)
{
	pthread_mutex_lock(&mutex->mutex);
	hq_add(mutex->data, value);
	pthread_mutex_unlock(&mutex->mutex);
}

void	*hq_mutex_pop(t_heap_queue_mutex *mutex)
{
	void	*item;

	pthread_mutex_lock(&mutex->mutex);
	item = hq_pop(mutex->data);
	pthread_mutex_unlock(&mutex->mutex);
	return (item);
}

size_t	hq_mutex_get_size(t_heap_queue_mutex *mutex)
{
	size_t	size;

	pthread_mutex_lock(&mutex->mutex);
	size = mutex->data->size;
	pthread_mutex_lock(&mutex->mutex);
	return (size);
}

bool	hq_compare_coder_id(t_heap_queue_mutex *mutex, size_t id)
{
	bool	equals;

	pthread_mutex_lock(&mutex->mutex);
	equals = mutex->data->size && ((t_coder*) mutex->data->data[0].data)->id == id;
	pthread_mutex_unlock(&mutex->mutex);
	return (equals);
}
