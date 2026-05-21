/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:22:11 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:27:09 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	set_voidp_mutex(t_voidp_mutex *mutex, t_typed_voidp data)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->data = data;
	pthread_mutex_unlock(&mutex->mutex);
}
void	set_size_t_mutex(t_size_t_mutex *mutex, size_t data)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->data = data;
	pthread_mutex_unlock(&mutex->mutex);
}

void	set_bool_mutex(t_bool_mutex *mutex, bool data)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->data = data;
	pthread_mutex_unlock(&mutex->mutex);
}

void	set_heap_queue_mutex(t_heap_queue_mutex *mutex, t_heap_queue *value)
{
	pthread_mutex_lock(&mutex->mutex);
	mutex->data = value;
	pthread_mutex_unlock(&mutex->mutex);
}
