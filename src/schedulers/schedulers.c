/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedulers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 12:50:14 by smenard           #+#    #+#             */
/*   Updated: 2026/06/18 12:50:17 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

size_t	get_key_fifo(void *el)
{
	(void)el;
	return (get_time_us());
}

size_t	get_key_edf(void *el)
{
	t_coder	*coder;
	size_t	key;

	coder = (t_coder *)el;
	pthread_mutex_lock(&coder->mutex);
	key = coder->last_compile_timestamp + coder->shared->time_to_burnout;
	pthread_mutex_unlock(&coder->mutex);
	return (key);
}
