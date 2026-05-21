/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:04:32 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 19:52:59 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/headers/coders_lib.h"
#include "headers/lib.h"
#include "utils/headers/utils.h"

static bool	should_continue(t_shared_ctx *shared)
{
	bool shoud_continue ;
	pthread_mutex_lock(&shared->run.mutex);
	shoud_continue = shared->run.data;
	pthread_mutex_unlock(&shared->run.mutex);
	return (shoud_continue);
}

void	*coder_routine(void *data)
{
	t_coder	*self;
	size_t	i;

	i = 0;
	self = (t_coder *)data;
	if (self->id % 2)
		usleep(50);
	// pthread_cond_timedwait(
	// 		pthread_cond_t *restrict cond,
	// 		pthread_mutex_t *restrict mutex,
	// 		const struct timespec *restrict abstime
	// );
	self->last_compile_timestamp = get_time_ms();
	ft_log_debug(&self->shared, "started routine", &self->id);
	while (should_continue(&self->shared))
	{
		compile(self);
		debug(self);
		refactor(self);
		i++;
		if (i == self->shared.number_of_compiles)
		{
			self->done = true;
			break ;
		}
	}
	return (NULL);
}
