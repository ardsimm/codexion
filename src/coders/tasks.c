/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:08:06 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 19:36:23 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongles/headers/dongles.h"
#include "headers/lib.h"
#include "utils/headers/utils.h"

static int	take_dongles(t_coder *self)
{
	request_dongle(self, self->dongle_left);
	request_dongle(self, self->dongle_right);
	if (!can_take_dongle(self, self->dongle_left) || !can_take_dongle(self,
			self->dongle_left))
		return (FAILURE);
	take_dongle(self, self->dongle_left);
	take_dongle(self, self->dongle_right);
	return (SUCCESS);
}

static void	release_dongles(t_coder *self)
{
	release_dongle(self->dongle_left);
	release_dongle(self->dongle_right);
}

void	compile(t_coder *self)
{
	while (take_dongles(self) == FAILURE)
		usleep(10);
	set_size_t_mutex(&self->last_compile_timestamp, get_time_ms());
	ft_log_info(&self->shared, "has started compiling", &self->id);
	usleep(self->shared.time_to_compile);
	release_dongles(self);
}

void	debug(t_coder *self)
{
	ft_log_info(&self->shared, "is debugging", &self->id);
	usleep(self->shared.time_to_debug);
}

void	refactor(t_coder *self)
{
	ft_log_info(&self->shared, "is refactoring", &self->id);
	usleep(self->shared.time_to_refactor);
}
