/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:04:32 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:29:14 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/headers/coders_lib.h"
#include "headers/lib.h"
#include "utils/headers/utils.h"

bool	should_continue(t_shared_ctx *shared)
{
	bool	result;

	pthread_mutex_lock(&shared->mutex);
	result = shared->run;
	pthread_mutex_unlock(&shared->mutex);
	return (result);
}

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
	pthread_mutex_lock(&self->mutex);
	self->last_compile_timestamp = get_time_us();
	pthread_mutex_unlock(&self->mutex);
	ft_log_debug(self->shared, "started routine", &self->id);
	while (should_continue(self->shared))
	{
		compile(self);
		debug(self);
		refactor(self);
		i++;
		if (i == self->shared->number_of_compiles)
		{
			pthread_mutex_lock(&self->mutex);
			self->done = true;
			pthread_mutex_unlock(&self->mutex);
			break ;
		}
	}
	return (NULL);
}
