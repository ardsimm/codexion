/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:08:06 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 14:55:19 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/headers/coders_lib.h"
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
	while (get_bool_value(&self->shared->run, &self->shared->mutex)
			&& ( !can_take_dongle_lock(self, self->dongle_left) || !can_take_dongle_lock(self, self->dongle_right) ))
		usleep(10);
	take_dongle(self, self->dongle_left);
	take_dongle(self, self->dongle_right);
}

// static void	take_dongles(t_coder *self)
// {
// 	while (!can_take_dongle_lock(self, self->dongle_left))
// 		usleep(10);
// 	take_dongle(self, self->dongle_left);
// 	while (!can_take_dongle_lock(self, self->dongle_right))
// 		usleep(10);
// 	take_dongle(self, self->dongle_right);
// }

void	compile(t_coder *self)
{
	request_dongle(self, self->dongle_left);
	request_dongle(self, self->dongle_right);
	take_dongles(self);
	set_size_t_value(&self->last_compile_timestamp, get_time_us(),
		&self->mutex);
	ft_log_info(self->shared, "is compiling", &self->id);
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
