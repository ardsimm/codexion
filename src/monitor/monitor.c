/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:03:38 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 19:39:15 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"
#include <pthread.h>

static pthread_t	*create_threads(t_ctx *ctx)
{
	pthread_t	*threads;
	size_t		i;

	threads = ft_calloc(ctx->coders_count, sizeof(pthread_t));
	if (!threads)
		return (NULL);
	i = 0;
	while (i < ctx->coders_count)
	{
		pthread_create(&threads[i], NULL, coder_routine, &ctx->coders[i]);
		i++;
	}
	return (threads);
}

static bool	should_stop(t_ctx *ctx)
{
	size_t	i;
	bool	all_done;

	i = 0;
	all_done = true;
	while (i < ctx->coders_count)
	{
		if (ctx->coders[i].last_compile_timestamp > 0
			&& !ctx->coders[i].done
			&& get_time_ms() > ctx->coders[i].last_compile_timestamp
			+ ctx->shared.time_to_burnout)
		{
			printf("last compile timestamp: %zu, time_to_burnout: %d, tv_usec:%zu\n",
				ctx->coders[i].last_compile_timestamp,
				ctx->shared.time_to_burnout, get_time_ms());
			printf("diff: %zu\n", ctx->coders[i].last_compile_timestamp
				+ ctx->shared.time_to_burnout - get_time_ms());
			pthread_mutex_lock(&ctx->shared.run.mutex);
			ctx->shared.run.data = false;
			pthread_mutex_unlock(&ctx->shared.run.mutex);
			ft_log_error(&ctx->shared, "burned out", &ctx->coders[i].id);
			return (true);
		}
		{
			all_done &= ctx->coders[i].done;
			i++;
		}
	}
	return (all_done);
}

void	*monitor_simulation(t_ctx *ctx)
{
	pthread_t	*threads;

	threads = create_threads(ctx);
	if (!threads)
		return (NULL);
	while (!should_stop(ctx))
	{
		ft_log_debug(&ctx->shared, "in loop", NULL);
		usleep(10);
	}
	return (free_return((void *[]){threads}, 0, NULL));
}
