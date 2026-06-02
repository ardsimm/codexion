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

int	init(t_ctx *ctx)
{
	int32_t	i;
	int		dongle_init_result;

	if (init_ctx(ctx) == FAILURE)
		return (FAILURE);
	i = 0;
	while (((size_t)i) < ctx->shared.coders_count)
		dongle_init_result = init_dongle((uint32_t)i++, ctx);
	if (dongle_init_result == MEMORY_ALLOCATION_FAILED)
	{
		dongles_free(ctx->dongles, ctx->shared.coders_count);
		return (free_ctx_return(ctx, FAILURE));
	}
	else if (dongle_init_result == MUTEX_INIT_FAILED)
	{
		while (i > 0)
		{
			hq_free(ctx->dongles[--i].hq);
		}
		return (free_ctx_return(ctx, FAILURE));
	}
	i = 0;
	while (((size_t)i) < ctx->shared.coders_count)
		init_coder(i++, ctx);
	return (SUCCESS);
}
