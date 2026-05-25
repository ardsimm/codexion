/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <your@email.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:53:03 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:08:22 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "heap_queue/headers/heap_queue.h"
#include "logging/headers/logging.h"
#include "utils/headers/utils.h"

static bool	dongle_cooldown_passed(long last_use_ts, size_t dongle_cooldown)
{
	size_t	time_since_last_use;

	time_since_last_use = get_time_us() - last_use_ts;
	return (time_since_last_use >= dongle_cooldown);
}

bool	can_take_dongle(t_coder *coder, t_dongle *dongle)
{
	bool	can_take;

	can_take = (!dongle->in_use
			&& ((t_coder *)dongle->hq->data[0].data)->id == coder->id
			&& dongle_cooldown_passed(dongle->last_use_timestamp,
				coder->shared->dongle_cooldown));
	return (can_take);
}

int	request_dongle(t_coder *coder, t_dongle *dongle)
{
	if (hq_contains(dongle->hq, coder))
		return (FAILURE);
	hq_add(dongle->hq, coder);
	return (SUCCESS);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	if (!can_take_dongle(coder, dongle))
		return (FAILURE);
	dongle->in_use = true;
	hq_pop(dongle->hq);
	ft_log_info(coder->shared, "has taken a dongle", &coder->id);
	return (SUCCESS);
}

int	release_dongle(t_dongle *dongle)
{
	dongle->in_use = false;
	dongle->last_use_timestamp = get_time_us();
	return (SUCCESS);
}
