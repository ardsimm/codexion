/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:20:34 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 18:21:58 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

void	init_coder(int32_t i, t_ctx *ctx)
{
	int64_t	dongle_left_idx;
	int64_t	dongle_right_idx;

	dongle_left_idx = i - 1;
	if (dongle_left_idx < 0)
		dongle_left_idx = ctx->coders_count - 1;
	dongle_right_idx = i;
	if (dongle_right_idx > ctx->coders_count - 1)
		dongle_left_idx = 0;
	ctx->coders[i].id = i;
	ctx->coders[i].shared = ctx->shared;
	ctx->coders[i].dongle_left = &ctx->dongles[dongle_left_idx];
	ctx->coders[i].dongle_right = &ctx->dongles[dongle_right_idx];
	hq_add(ctx->coders[i].dongle_left->hq, &ctx->coders[i]);
	hq_add(ctx->coders[i].dongle_right->hq, &ctx->coders[i]);
}
