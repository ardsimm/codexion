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

static void	take_dongles(t_coder *self)
{
	const t_dongle	*first = get_first_dongle(self);
	const t_dongle	*second = get_second_dongle(self);

	while (get_bool_value(&self->shared->run, &self->shared->mutex))
	{
		pthread_mutex_lock((pthread_mutex_t *)&first->mutex);
		pthread_mutex_lock((pthread_mutex_t *)&second->mutex);
		if (can_take_dongle(self, self->dongle_left) && can_take_dongle(self,
				self->dongle_right))
		{
			self->dongle_left->in_use = true;
			hq_pop(self->dongle_left->hq);
			self->dongle_right->in_use = true;
			hq_pop(self->dongle_right->hq);
			pthread_mutex_unlock((pthread_mutex_t *)&second->mutex);
			pthread_mutex_unlock((pthread_mutex_t *)&first->mutex);
			ft_log_info(self->shared, "has taken a dongle", &self->id);
			ft_log_info(self->shared, "has taken a dongle", &self->id);
			return ;
		}
		pthread_mutex_unlock((pthread_mutex_t *)&second->mutex);
		pthread_mutex_unlock((pthread_mutex_t *)&first->mutex);
		usleep(10);
	}
}

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
