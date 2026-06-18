/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 12:49:42 by smenard           #+#    #+#             */
/*   Updated: 2026/06/18 12:53:36 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "init/headers/init_lib.h"

static int	handle_dongle_memory_allocation_failed(t_ctx *ctx)
{
	dongles_free(ctx->dongles, ctx->shared.coders_count);
	return (FAILURE);
}

static int	handle_dongle_mutex_init_failed(t_ctx *ctx, int i)
{
	while (i > 0)
	{
		hq_free(ctx->dongles[--i].hq);
	}
	return (FAILURE);
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
	{
		if (init_coder(i++, ctx) != SUCCESS)
		{
			dongles_free(ctx->dongles, ctx->shared.coders_count);
			coders_free(ctx->coders, i);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
