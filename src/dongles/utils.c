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

static bool	dongle_cooldown_passed(long last_use_ts, size_t dongle_cooldown)
{
	size_t	curr_time;

	curr_time = get_time_us();
	return (curr_time - (size_t)last_use_ts > dongle_cooldown);
}

bool	can_take_dongle(t_coder *coder, t_dongle *dongle)
{
	return (!dongle->in_use
		&& ((t_coder *)dongle->hq->data[0].data)->id == coder->id
		&& dongle_cooldown_passed(dongle->last_use_timestamp,
			coder->shared->dongle_cooldown));
}

int	request_dongle(t_coder *coder, t_dongle *dongle)
{
	int	result;

	pthread_mutex_lock(&dongle->mutex);
	if (hq_contains(dongle->hq, coder))
		result = FAILURE;
	else
	{
		result = SUCCESS;
		hq_add(dongle->hq, coder);
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (result);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	int	result;

	pthread_mutex_lock(&dongle->mutex);
	if (!can_take_dongle(coder, dongle))
		result = FAILURE;
	else
	{
		dongle->in_use = true;
		hq_pop(dongle->hq);
		ft_log_info(coder->shared, "has taken a dongle", &coder->id);
		result = SUCCESS;
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (result);
}

int	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->in_use = false;
	dongle->last_use_timestamp = get_time_us();
	pthread_mutex_unlock(&dongle->mutex);
	return (SUCCESS);
}
