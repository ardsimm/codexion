/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:03:38 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 16:04:58 by smenard          ###   ########.fr       */
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
	size_t			i;
	struct timeval	tv;
	bool			all_done;

	i = 0;
	all_done = false;
	while (i < ctx->coders_count)
	{
		gettimeofday(&tv, NULL);
		if (ctx->coders[i].last_compile_timestamp
			+ ctx->shared.time_to_burnout > (size_t)tv.tv_usec)
		{
			pthread_mutex_lock(&ctx->shared.run_mutex);
			ctx->shared.run = false;
			pthread_mutex_unlock(&ctx->shared.run_mutex);
			ft_log_error(&ctx->shared, "burned out", &ctx->coders[i].id);
			return (true);
		}
		all_done &= ctx->coders[i++].done;
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
		usleep(10);
	return (free_return((void *[]){threads}, 0, NULL));
}
