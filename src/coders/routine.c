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
#include "mutex/headers/mutex.h"
#include "utils/headers/utils.h"

static bool	should_continue(t_shared_ctx *shared)
{
	return (get_bool_mutex(&shared->run));
}

void	*coder_routine(void *data)
{
	t_coder	*self;
	size_t	i;

	i = 0;
	self = (t_coder *)data;
	if (self->id % 2)
		usleep(50);
	// set_size_t_mutex(&self->last_compile_timestamp, get_time_ms());
	ft_log_debug(&self->shared, "started routine", &self->id);
	while (should_continue(&self->shared))
	{
		// ft_log_debug(&self->shared, "Before compile", &self->id);
		compile(self);
		// ft_log_debug(&self->shared, "Before debug", &self->id);
		debug(self);
		// ft_log_debug(&self->shared, "Before refactor", &self->id);
		refactor(self);
		i++;
		if (i == self->shared.number_of_compiles)
		{
			ft_log_debug(&self->shared, "Finished !", &self->id);
			set_bool_mutex(&self->done, true);
			break ;
		}
	}
	return (NULL);
}
