/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:23:14 by smenard           #+#    #+#             */
/*   Updated: 2026/06/18 12:25:25 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

int	init_dongle(uint32_t i, t_ctx *ctx)
{
	t_get_key	get_key;

	if (ctx->scheduler == FIFO)
		get_key = get_key_fifo;
	else
		get_key = get_key_edf;
	ctx->dongles[i].id = i;
	if (pthread_mutex_init(&ctx->dongles[i].mutex, NULL))
		return (MUTEX_INIT_FAILED);
	ctx->dongles[i].hq = hq_init(2, sizeof(t_heap_queue_item), get_key);
	if (!ctx->dongles[i].hq || !ctx->dongles[i].hq->data)
		return (MEMORY_ALLOCATION_FAILED);
	ctx->dongles[i].cooldown = ctx->shared.dongle_cooldown;
	return (SUCCESS);
}
