/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 15:46:41 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

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
	printf("after parse\n");
	if (!ctx)
		return (raise_error(NULL, "Parsing error"));
	if (init(ctx) == FAILURE)
	{
		printf("after init (failure)\n");
		ft_log_error(NULL, "Initialization error", NULL);
		return ((int)free_return_int((void *[]){ctx}, 1, EXIT_FAILURE));
	}
	printf("after init (success)\n");
	if (ctx->shared.coders_count <= 1)
		return (raise_error(&ctx->shared,
				"cannot run the simulation with less than 2 coders"));
	exit_value = EXIT_SUCCESS;
	if (monitor_simulation(ctx) == FAILURE)
		exit_value = EXIT_FAILURE;
	printf("after monitor\n");
	dongles_free(ctx->dongles, ctx->shared.coders_count);
	printf("adter dongles free\n");
	free_all((void *[]){ctx->dongles, ctx->coders, ctx}, 3);
	return (exit_value);
}
