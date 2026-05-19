/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:01:17 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 15:43:28 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	print_hq(t_heap_queue *hq)
{
	printf("Heap queue size: %zu\n", hq->size);
	for (size_t i = 0; i < hq->size; i++)
		printf("hq[%zu]: %d\n", i, *(int *)hq->data[i].data);
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
		return ((int)free_return_int((void *[]){ctx}, 1,
				EXIT_FAILURE));
	}
	monitor_simulation(ctx);
	free_all((void *[]){ctx->dongles, ctx->coders, ctx}, 3);
	return (EXIT_SUCCESS);
}
