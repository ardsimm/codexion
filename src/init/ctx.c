/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:26:07 by smenard           #+#    #+#             */
/*   Updated: 2026/06/18 12:49:22 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

int	init_ctx(t_ctx *ctx)
{
	if (pthread_mutex_init(&ctx->shared.mutex, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&ctx->shared.logging_mutex, NULL))
	{
		pthread_mutex_destroy(&ctx->shared.mutex);
		return (FAILURE);
	}
	if (pthread_mutex_init(&ctx->shared.start, NULL))
	{
		pthread_mutex_destroy(&ctx->shared.mutex);
		pthread_mutex_destroy(&ctx->shared.logging_mutex);
		return (FAILURE);
	}
	ctx->shared.logging_active = true;
	ctx->shared.run = true;
	ctx->shared.timestamp_start = get_time_us();
	ctx->coders = ft_calloc(ctx->shared.coders_count, sizeof(t_coder));
	if (!ctx->coders)
		return (FAILURE);
	ctx->dongles = ft_calloc(ctx->shared.coders_count, sizeof(t_dongle));
	if (!ctx->dongles)
		return (free_return_int((void *[]){ctx->coders, ctx->dongles}, 2,
			FAILURE));
	return (SUCCESS);
}
