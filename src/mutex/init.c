/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:30:50 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:45:05 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/defines.h"
#include "headers/lib.h"
#include "mutex/headers/mutex.h"

void	init_voidp_mutex(t_voidp_mutex *mutex, t_typed_voidp value)
{
	pthread_mutex_init(&mutex->mutex, NULL);
	mutex->data = value;
}

void	init_size_t_mutex(t_size_t_mutex *mutex, size_t value)
{
	pthread_mutex_init(&mutex->mutex, NULL);
	mutex->data = value;
}

void	init_bool_mutex(t_bool_mutex *mutex, bool value)
{
	pthread_mutex_init(&mutex->mutex, NULL);
	mutex->data = value;
}

void	init_heap_queue_mutex(t_heap_queue_mutex *mutex, t_heap_queue *value)
{
	pthread_mutex_init(&mutex->mutex, NULL);
	set_heap_queue_mutex(mutex, value);
}
