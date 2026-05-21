/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:23:14 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:23:31 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/defines.h"
#include "headers/lib.h"

int	init_dongle(uint32_t i, t_ctx *ctx)
{
	ctx->dongles[i].id = i;
	ctx->dongles[i].hq = hq_init(2, sizeof(t_coder), get_key_fifo,
			update_key_fifo);
	if (!ctx->dongles[i].hq)
		return (FAILURE);
	pthread_mutex_init(&ctx->dongles[i].in_use.mutex, NULL);
	ctx->dongles[i].in_use.data = false;
	ctx->dongles[i].cooldown = ctx->shared.dongle_cooldown;
	return (SUCCESS);
}
