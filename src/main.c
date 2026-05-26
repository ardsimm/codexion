/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 19:38:14 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug/headers/debug.h"
#include "headers/lib.h"

int	main(int ac, char **av)
{
	t_ctx	*ctx;

	ctx = parse(ac, av);
	if (!ctx)
	{
		ft_log_error(NULL, "Parsing error", NULL);
		return (FAILURE);
	}
	if (init(ctx) == FAILURE)
	{
		ft_log_error(NULL, "Initialization error", NULL);
		return ((int)free_return_int((void *[]){ctx}, 1, EXIT_FAILURE));
	}
	print_ctx(ctx);
	monitor_simulation(ctx);
	free_all((void *[]){ctx->dongles, ctx->coders, ctx}, 3);
	return (EXIT_SUCCESS);
}
