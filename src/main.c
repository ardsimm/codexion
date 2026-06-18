/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/06/18 12:57:54 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static void	free_ctx(t_ctx *ctx)
{
	dongles_free(ctx->dongles, ctx->shared.coders_count);
	coders_free(ctx->coders, ctx->shared.coders_count);
	pthread_mutex_destroy(&ctx->shared.mutex);
	pthread_mutex_destroy(&ctx->shared.logging_mutex);
	pthread_mutex_destroy(&ctx->shared.start);
	free_all((void *[]){ctx->dongles, ctx->coders, ctx}, 3);
}

static int	raise_error(t_shared_ctx *ctx, char *err)
{
	ft_log_error(ctx, err, NULL);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_ctx	*ctx;
	int		exit_value;

	ctx = parse(ac, av);
	if (!ctx)
		return (raise_error(NULL, "Parsing error"));
	if (init(ctx) != SUCCESS)
	{
		ft_log_error(NULL, "Initialization error", NULL);
		return ((int)free_return_int((void *[]){ctx, ctx->coders, ctx->dongles},
			3, EXIT_FAILURE));
	}
	if (ctx->shared.coders_count < 1)
	{
		free_ctx(ctx);
		return (raise_error(&ctx->shared,
				"cannot run the simulation with less than 1 coders"));
	}
	exit_value = EXIT_SUCCESS;
	if (monitor_simulation(ctx) != SUCCESS)
		exit_value = EXIT_FAILURE;
	free_ctx(ctx);
	return (exit_value);
}
