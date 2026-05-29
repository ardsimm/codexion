/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:43:00 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 14:45:51 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

bool	get_bool_value(bool *ptr, pthread_mutex_t *mutex)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *ptr;
	pthread_mutex_unlock(mutex);
	return (value);
}

size_t	get_size_t_value(size_t *ptr, pthread_mutex_t *mutex)
{
	size_t	value;

	pthread_mutex_lock(mutex);
	value = *ptr;
	pthread_mutex_unlock(mutex);
	return (value);
}
