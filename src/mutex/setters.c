/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:48:08 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 14:49:19 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	set_size_t_value(size_t *ptr, size_t value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*ptr = value;
	pthread_mutex_unlock(mutex);
}

void	set_bool_value(bool *ptr, bool value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*ptr = value;
	pthread_mutex_unlock(mutex);
}
