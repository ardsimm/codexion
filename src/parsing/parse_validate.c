/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:50:32 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 15:12:22 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static bool	validate_int_value(int value)
{
	return (value >= 0);
}

bool	validate_ctx(t_ctx *ctx)
{
	bool	valid;

	valid = true;
	valid &= validate_int_value(ctx->shared.coders_count);
	valid &= validate_int_value(ctx->shared.time_to_burnout);
	valid &= validate_int_value(ctx->shared.time_to_compile);
	valid &= validate_int_value(ctx->shared.time_to_debug);
	valid &= validate_int_value(ctx->shared.time_to_refactor);
	valid &= validate_int_value(ctx->shared.number_of_compiles);
	valid &= validate_int_value(ctx->shared.dongle_cooldown);
	valid &= ctx->scheduler == FIFO || ctx->scheduler == EDF;
	return (valid);
}
