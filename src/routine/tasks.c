/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:08:06 by smenard           #+#    #+#             */
/*   Updated: 2026/05/14 16:43:02 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static bool	can_take_dongles(const t_coder *self)
{
	const t_coder	*next_left = (t_coder *)self->dongle_left->hq->data[0].data;
	const t_coder	*next_right = (t_coder *)self->dongle_right->hq->data[0].data;

	return (next_left == self->id && !self->dongle_left->in_use
		&& next_right->id == self->id && !self->dongle_right->in_use);
}

static void	take_dongles(const t_coder *self)
{
	pthread_mutex_lock(&self->dongle_left->in_use_mutex);
	ft_log_info(&self->shared, "has taken a dongle", &self->id);
	pthread_mutex_lock(&self->dongle_right->in_use_mutex);
	ft_log_info(&self->shared, "has taken a dongle", &self->id);
}

void	compile(const t_coder *self)
{
	while (!can_take_dongles(self))
		usleep(10);
	take_dongles(self);
	hq_pop(self->dongle_left->hq);
	hq_pop(self->dongle_right->hq);
	ft_log_info(&self->shared, "is compiling", &self->id);
	usleep(self->shared.time_to_compile);
	hq_add(self->dongle_left->hq, &self->shared, self);
	hq_add(self->dongle_right->hq, &self->shared, self);
	pthread_mutex_unlock(&self->dongle_left->in_use_mutex);
	pthread_mutex_unlock(&self->dongle_right->in_use_mutex);
}

void	debug(const t_coder *self)
{
	ft_log_info(&self->shared, "is debugging", &self->id);
	usleep(self->shared.time_to_debug);
}

void	refactor(const t_coder *self)
{
	ft_log_info(&self->shared, "is refactoring", &self->id);
	usleep(self->shared.time_to_refactor);
}
