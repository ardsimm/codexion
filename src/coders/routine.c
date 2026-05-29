/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:04:32 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 15:26:59 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/headers/coders_lib.h"
#include "headers/lib.h"

void	*coder_routine(void *data)
{
	t_coder	*self;
	size_t	i;

	i = 0;
	self = (t_coder *)data;
	pthread_mutex_lock(&self->shared->start);
	pthread_mutex_unlock(&self->shared->start);
	if (self->id % 2)
		usleep(self->shared->time_to_compile / 2);
	set_size_t_value(&self->last_compile_timestamp, get_time_us(),
		&self->mutex);
	while (get_bool_value(&self->shared->run, &self->shared->mutex))
	{
		compile(self);
		debug(self);
		refactor(self);
		i++;
		if (i == self->shared->number_of_compiles)
		{
			set_bool_value(&self->done, true, &self->mutex);
			break ;
		}
	}
	return (NULL);
}
