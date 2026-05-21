/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <your@email.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:53:03 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 18:22:10 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "heap_queue/headers/heap_queue.h"
#include "utils/headers/utils.h"

static bool	dongle_cooldown_passed(long last_use_ts, size_t dongle_cooldown)
{
	size_t	time_since_last_use;

	time_since_last_use = get_time_ms() - last_use_ts;
	return (time_since_last_use >= dongle_cooldown);
}

bool	can_take_dongle(t_coder *coder, t_dongle *dongle)
{
	bool	can_take;

	pthread_mutex_lock(&dongle->in_use.mutex);
	can_take = (!dongle->in_use.data
			&& ((t_coder *)dongle->hq->data[0].data)->id == coder->id
			&& dongle_cooldown_passed(dongle->last_use_timestamp,
				coder->shared.dongle_cooldown));
	pthread_mutex_unlock(&dongle->in_use.mutex);
	return (can_take);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	if (!can_take_dongle(coder, dongle))
		return (FAILURE);
	pthread_mutex_lock(&dongle->in_use.mutex);
	dongle->in_use.data = true;
	pthread_mutex_unlock(&dongle->in_use.mutex);
	return (SUCCESS);
}

int	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->in_use.mutex);
	dongle->in_use.data = false;
	hq_update_keys(dongle->hq);
	dongle->last_use_timestamp = get_time_ms();
	pthread_mutex_unlock(&dongle->in_use.mutex);
	return (SUCCESS);
}
