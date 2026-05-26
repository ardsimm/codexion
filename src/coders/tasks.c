/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:08:06 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:14:33 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static bool	can_take_dongle_lock(t_coder *self, t_dongle *dongle)
{
	bool	result;

	pthread_mutex_lock(&dongle->mutex);
	result = can_take_dongle(self, dongle);
	pthread_mutex_unlock(&dongle->mutex);
	return (result);
}

static void	take_dongles(t_coder *self)
{
	while (!can_take_dongle_lock(self, self->dongle_left))
		usleep(10);
	take_dongle(self, self->dongle_left);
	while (!can_take_dongle_lock(self, self->dongle_right))
		usleep(10);
	take_dongle(self, self->dongle_right);
}

void	compile(t_coder *self)
{
	request_dongle(self, self->dongle_left);
	request_dongle(self, self->dongle_right);
	take_dongles(self);
	ft_log_debug(self->shared, "after take", &self->id);
	pthread_mutex_lock(&self->mutex);
	self->last_compile_timestamp = get_time_us();
	pthread_mutex_unlock(&self->mutex);
	ft_log_info(self->shared, "has started compiling", &self->id);
	usleep(self->shared->time_to_compile);
	release_dongle(self->dongle_left);
	release_dongle(self->dongle_right);
}

void	debug(t_coder *self)
{
	ft_log_info(self->shared, "is debugging", &self->id);
	usleep(self->shared->time_to_debug);
}

void	refactor(t_coder *self)
{
	ft_log_info(self->shared, "is refactoring", &self->id);
	usleep(self->shared->time_to_refactor);
}
