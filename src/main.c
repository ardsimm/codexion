/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/05/14 16:47:00 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

size_t	get_key(t_shared_ctx *ctx, void *el)
{
	(void) ctx;
	return *(size_t *)el;
}

static void	init_coder(uint32_t i, t_ctx *ctx)
{
	size_t	dongle_left_idx;
	size_t	dongle_right_idx;

	dongle_left_idx = i - 1;
	if (i < 0)
		dongle_left_idx = ctx->coders_count - 1;
	dongle_right_idx = i + 1;
	if (dongle_right_idx > ctx->coders_count - 1)
		dongle_left_idx = 0;
	ctx->coders[i].id = i;
	ctx->coders[i].shared = ctx->shared;
	ctx->coders[i].dongle_left = &ctx->dongles[dongle_left_idx];
	ctx->coders[i].dongle_right = &ctx->dongles[dongle_right_idx];
}

static void	init_dongle(uint32_t i, t_ctx *ctx)
{
	ctx->dongles[i].id = i;
	ctx->dongles[i].hq = hq_init(2, sizeof(t_coder), get_key);
	pthread_mutex_init(&ctx->dongles[i].in_use_mutex, NULL);
	ctx->dongles[i].cooldown = ctx->shared.dongle_cooldown;
}

static int	init(t_ctx *ctx)
{
	uint32_t	i;

	i = 0;
	pthread_mutex_init(&ctx->shared.logging_mutex, NULL);
	ctx->coders = ft_calloc(ctx->coders_count, sizeof(t_coder));
	if (!ctx->coders)
		return (FAILURE);
	while (i < ctx->coders_count)
		init_coder(i++, ctx);
	i = 0;
	ctx->dongles = ft_calloc(ctx->coders_count, sizeof(t_dongle));
	if (!ctx->dongles)
		return (free_return_int((void *[]){ctx->dongles}, 1,
			FAILURE));
	while (i < ctx->coders_count)
		init_dongle(i++, ctx);
	return (SUCCESS);
}

void	print_hq(t_heap_queue *hq)
{
	printf("Heap queue size: %zu	\n", hq->size);
	for (size_t i = 0; i < hq->size; i++)
		printf("hq[%zu]: %d\n", i, *(int*)hq->data[i].data);
}

int	main(int ac, char **av)
{
	t_ctx	*ctx;

	ctx = parse(ac, av);
	if (!ctx)
	{
		ft_log_error(&ctx->shared, "Parsing error", NULL);
		return (FAILURE);
	}
	if (init(ctx) == FAILURE)
	{
		ft_log_error(&ctx->shared, "Initialization error", NULL);
		return ((int)free_return_int((void *[]){ctx->scheduler, ctx}, 2,
			EXIT_FAILURE));
	}
	ft_log_debug(&ctx->shared, "Parsing successful", NULL);
	monitor_simulation(ctx);
	free_all((void *[]){ctx->scheduler, ctx->dongles, ctx->coders, ctx}, 4);
	return (EXIT_SUCCESS);
}
