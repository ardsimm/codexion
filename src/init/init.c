/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:20:03 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:26:03 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "init/headers/init_lib.h"

static int	free_ctx_return(t_ctx *ctx, int value)
{
	free(ctx->coders);
	free(ctx->dongles);
	return (value);
}

static int	handle_dongle_memory_allocation_failed(t_ctx *ctx)
{
	dongles_free(ctx->dongles, ctx->shared.coders_count);
	return (free_ctx_return(ctx, FAILURE));
}

static int	handle_dongle_mutex_init_failed(t_ctx *ctx, int i)
{
	while (i > 0)
	{
		hq_free(ctx->dongles[--i].hq);
	}
	return (free_ctx_return(ctx, FAILURE));
}

int	init(t_ctx *ctx)
{
	int32_t	i;
	int		dongle_init_result;

	if (init_ctx(ctx) != SUCCESS)
		return (FAILURE);
	i = 0;
	dongle_init_result = SUCCESS;
	while (((size_t)i) < ctx->shared.coders_count
		&& dongle_init_result == SUCCESS)
		dongle_init_result = init_dongle((uint32_t)i++, ctx);
	if (dongle_init_result == MEMORY_ALLOCATION_FAILED)
		return (handle_dongle_memory_allocation_failed(ctx));
	else if (dongle_init_result == MUTEX_INIT_FAILED)
		return (handle_dongle_mutex_init_failed(ctx, i));
	i = 0;
	while (((size_t)i) < ctx->shared.coders_count)
		init_coder(i++, ctx);
	return (SUCCESS);
}
