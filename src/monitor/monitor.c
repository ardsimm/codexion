/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:03:38 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:35:23 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

static pthread_t	*create_threads(t_ctx *ctx)
{
	pthread_t	*threads;
	size_t		i;

	threads = ft_calloc(ctx->shared.coders_count, sizeof(pthread_t));
	if (!threads)
		return (NULL);
	i = 0;
	while (i < ctx->shared.coders_count)
	{
		pthread_create(&threads[i], NULL, coder_routine, &ctx->coders[i]);
		i++;
	}
	return (threads);
}

static bool	check_burnout(t_ctx *ctx, t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	if (coder->last_compile_timestamp > 0 && !coder->done
		&& get_time_us() > coder->last_compile_timestamp
		+ ctx->shared.time_to_burnout)
	{
		pthread_mutex_unlock(&coder->mutex);
		pthread_mutex_lock(&ctx->shared.mutex);
		ctx->shared.run = false;
		pthread_mutex_unlock(&ctx->shared.mutex);
		ft_log_error(&ctx->shared, "burned out", &coder->id);
		return (true);
	}
	pthread_mutex_unlock(&coder->mutex);
	return (false);
}

static bool	should_stop(t_ctx *ctx)
{
	size_t	i;
	bool	all_done;

	i = 0;
	all_done = true;
	while (i < ctx->shared.coders_count)
	{
		if (check_burnout(ctx, &ctx->coders[i]))
			return (true);
		pthread_mutex_lock(&ctx->coders[i].mutex);
		all_done &= ctx->coders[i].done;
		pthread_mutex_unlock(&ctx->coders[i].mutex);
		i++;
	}
	if (all_done)
	{
		pthread_mutex_lock(&ctx->shared.mutex);
		ctx->shared.run = false;
		pthread_mutex_unlock(&ctx->shared.mutex);
	}
	return (all_done);
}

static void	join_threads(pthread_t *threads, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		pthread_join(threads[i++], NULL);
}

void	*monitor_simulation(t_ctx *ctx)
{
	pthread_t	*threads;

	pthread_mutex_lock(&ctx->shared.start);
	threads = create_threads(ctx);
	pthread_mutex_unlock(&ctx->shared.start);
	if (!threads)
		return (NULL);
	while (!should_stop(ctx))
		usleep(10);
	ft_log_debug(&ctx->shared, "joining threads...", NULL);
	join_threads(threads, ctx->shared.coders_count);
	ft_log_debug(NULL, "Finished, exiting...", NULL);
	return (free_return((void *[]){threads}, 0, NULL));
}
