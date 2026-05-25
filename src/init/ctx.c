/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:26:07 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:08:02 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

int	init_ctx(t_ctx *ctx)
{
	pthread_mutex_init(&ctx->shared.mutex, NULL);
	pthread_mutex_init(&ctx->shared.logging_mutex, NULL);
	ctx->shared.logging_active = true;
	ctx->shared.run = true;
	ctx->shared.timestamp_start = get_time_us();
	ctx->coders = ft_calloc(ctx->coders_count, sizeof(t_coder));
	if (!ctx->coders)
		return (FAILURE);
	ctx->dongles = ft_calloc(ctx->coders_count, sizeof(t_dongle));
	if (!ctx->dongles)
		return (free_return_int((void *[]){ctx->dongles}, 1, FAILURE));
	return (SUCCESS);
}
