/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:20:03 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 15:59:49 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static void	init_coder(int32_t i, t_ctx *ctx)
{
	int64_t			dongle_left_idx;
	int64_t			dongle_right_idx;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
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
	ctx->coders[i].last_compile_timestamp = tv.tv_usec;
	hq_add(ctx->coders[i].dongle_left->hq, &ctx->coders[i]);
	hq_add(ctx->coders[i].dongle_right->hq, &ctx->coders[i]);
}

static void	init_dongle(uint32_t i, t_ctx *ctx)
{
	ctx->dongles[i].id = i;
	ctx->dongles[i].hq = hq_init(2, sizeof(t_coder), get_key_fifo,
			update_key_fifo);
	pthread_mutex_init(&ctx->dongles[i].in_use_mutex, NULL);
	ctx->dongles[i].cooldown = ctx->shared.dongle_cooldown;
}

static int	init_ctx(t_ctx *ctx)
{
	pthread_mutex_init(&ctx->shared.logging_mutex, NULL);
	pthread_mutex_init(&ctx->shared.run_mutex, NULL);
	ctx->shared.run = true;
	ctx->coders = ft_calloc(ctx->coders_count, sizeof(t_coder));
	if (!ctx->coders)
		return (FAILURE);
	ctx->dongles = ft_calloc(ctx->coders_count, sizeof(t_dongle));
	if (!ctx->dongles)
		return (free_return_int((void *[]){ctx->dongles}, 1, FAILURE));
	return (SUCCESS);
}

int	init(t_ctx *ctx)
{
	uint32_t	i;

	if (init_ctx(ctx) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < ctx->coders_count)
		init_dongle(i++, ctx);
	i = 0;
	while (i < ctx->coders_count)
		init_coder(i++, ctx);
	return (SUCCESS);
}
