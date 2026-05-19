/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:04:32 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 16:01:59 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/routine_lib.h"

static bool	should_continue(t_shared_ctx *shared)
{
	bool shoud_continue ;
	pthread_mutex_lock(&shared->run_mutex);
	shoud_continue = shared->run;
	pthread_mutex_lock(&shared->run_mutex);
	return (shoud_continue);
}

void	*coder_routine(void *data)
{
	t_coder	*self;
	size_t	i;

	i = 0;
	self = (t_coder *)data;
	while (should_continue(&self->shared))
	{
		compile(self);
		refactor(self);
		debug(self);
		i++;
		if (i == self->shared.number_of_compiles)
			self->done = true;
	}
	return (NULL);
}
