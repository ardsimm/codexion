/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:08:06 by smenard           #+#    #+#             */
/*   Updated: 2026/05/19 17:50:35 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static int	take_dongles(t_coder *self)
{
	int	dongle_left_result;
	int	dongle_right_result;

	dongle_left_result = take_dongle(self, self->dongle_left);
	dongle_right_result = take_dongle(self, self->dongle_right);
	if (dongle_left_result == FAILURE || dongle_right_result == FAILURE)
	{
		if (dongle_left_result == SUCCESS)
			release_dongle(self->dongle_right);
		else if (dongle_right_result == SUCCESS)
			release_dongle(self->dongle_right);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	release_dongles(t_coder *self)
{
	release_dongle(self->dongle_left);
	release_dongle(self->dongle_right);
}

void	compile(t_coder *self)
{
	struct timeval	tv;

	while (take_dongles(self) == FAILURE)
		usleep(10);
	gettimeofday(&tv, NULL);
	self->last_compile_timestamp = tv.tv_usec;
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
