/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:05:02 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:11:24 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static int	ft_log(t_shared_ctx *ctx, t_log_level log_level, size_t *coder_id,
		char *str)
{
	size_t	curr_usec_delta;

	if (log_level < LOG_LEVEL)
		return (FAILURE);
	if (!ctx)
	{
		printf("0 (nil) %s\n", str);
		return (SUCCESS);
	}
	// pthread_mutex_lock(&ctx->mutex);
	// if (!ctx->run && coder_id)
	// {
	// 	pthread_mutex_unlock(&ctx->mutex);
	// 	return (FAILURE);
	// }
	// pthread_mutex_unlock(&ctx->mutex);
	curr_usec_delta = (get_time_us() - ctx->timestamp_start) / 1000;
	pthread_mutex_lock(&ctx->logging_mutex);
	if (coder_id)
		printf("%ld %zu %s\n", curr_usec_delta, *coder_id, str);
	else
		printf("%ld %s\n", curr_usec_delta, str);
	pthread_mutex_unlock(&ctx->logging_mutex);
	return (SUCCESS);
}

int	ft_log_debug(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, DEBUG, coder_id, message));
}

int	ft_log_info(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, INFO, coder_id, message));
}

int	ft_log_warn(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, WARN, coder_id, message));
}

int	ft_log_error(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, ERROR, coder_id, message));
}
