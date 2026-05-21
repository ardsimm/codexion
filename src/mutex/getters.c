/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:18:10 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:21:52 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

size_t	get_size_t_mutex(t_size_t_mutex *mutex)
{
	size_t	data;

	pthread_mutex_lock(&mutex->mutex);
	data = mutex->data;
	pthread_mutex_unlock(&mutex->mutex);
	return (data);
}

t_typed_voidp	get_voidp_mutex(t_voidp_mutex *mutex)
{
	t_typed_voidp	data;

	pthread_mutex_lock(&mutex->mutex);
	data = mutex->data;
	pthread_mutex_unlock(&mutex->mutex);
	return (data);
}

bool	get_bool_mutex(t_bool_mutex *mutex)
{
	bool	data;

	pthread_mutex_lock(&mutex->mutex);
	data = mutex->data;
	pthread_mutex_unlock(&mutex->mutex);
	return (data);
}
