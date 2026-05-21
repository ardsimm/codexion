/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:26:07 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:47:51 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

int	init_ctx(t_ctx *ctx)
{
	init_bool_mutex(ctx->shared.logging_active, true);
	init_bool_mutex(ctx->shared.run, true);
	ctx->shared.timestamp_start = get_time_ms();
	ctx->coders = ft_calloc(ctx->coders_count, sizeof(t_coder));
	if (!ctx->coders)
		return (FAILURE);
	ctx->dongles = ft_calloc(ctx->coders_count, sizeof(t_dongle));
	if (!ctx->dongles)
		return (free_return_int((void *[]){ctx->dongles}, 1, FAILURE));
	return (SUCCESS);
}
