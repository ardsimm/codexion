/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:26:07 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 19:50:42 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

int	init_ctx(t_ctx *ctx)
{
	pthread_mutex_init(&ctx->shared.logging_active.mutex, NULL);
	pthread_mutex_init(&ctx->shared.run.mutex, NULL);
	ctx->shared.run.data = true;
	ctx->shared.logging_active.data = true;
	ctx->shared.timestamp_start = get_time_ms();
	ctx->coders = ft_calloc(ctx->coders_count, sizeof(t_coder));
	if (!ctx->coders)
		return (FAILURE);
	ctx->dongles = ft_calloc(ctx->coders_count, sizeof(t_dongle));
	if (!ctx->dongles)
		return (free_return_int((void *[]){ctx->dongles}, 1, FAILURE));
	pthread_cond_init(&ctx->shared.start_condition.cond, NULL);
	pthread_mutex_init(&ctx->shared.start_condition.mutex, NULL);
	ctx->shared.start_condition.value = -1;
	return (SUCCESS);
}
