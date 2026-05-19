/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <your@email.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:53:03 by smenard           #+#    #+#             */
/*   Updated: 2026/05/19 17:50:35 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "heap_queue/headers/heap_queue.h"

static bool	dongle_cooldown_passed(long last_use_ts, size_t dongle_cooldown)
{
	struct timeval	tv;
	size_t			time_since_last_use;

	gettimeofday(&tv, NULL);
	time_since_last_use = tv.tv_usec - last_use_ts;
	return (time_since_last_use >= dongle_cooldown);
}

bool	can_take_dongle(t_coder *coder, t_dongle *dongle)
{
	bool	can_take;

	pthread_mutex_lock(&dongle->in_use_mutex);
	can_take = (!dongle->in_use
			&& ((t_coder *)dongle->hq->data[0].data)->id == coder->id
			&& dongle_cooldown_passed(dongle->last_use_timestamp,
				coder->shared.dongle_cooldown));
	pthread_mutex_unlock(&dongle->in_use_mutex);
	return (can_take);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	if (!can_take_dongle(coder, dongle))
		return (FAILURE);
	pthread_mutex_lock(&dongle->in_use_mutex);
	dongle->in_use = true;
	pthread_mutex_unlock(&dongle->in_use_mutex);
	return (SUCCESS);
}

int	release_dongle(t_dongle *dongle)
{
	struct timeval	tv;

	pthread_mutex_lock(&dongle->in_use_mutex);
	dongle->in_use = false;
	hq_update_keys(dongle->hq);
	gettimeofday(&tv, NULL);
	dongle->last_use_timestamp = tv.tv_usec;
	pthread_mutex_unlock(&dongle->in_use_mutex);
	return (SUCCESS);
}
