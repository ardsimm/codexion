/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:05:02 by smenard           #+#    #+#             */
/*   Updated: 2026/05/14 16:42:21 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static int	ft_log(
	t_shared_ctx *ctx,
	t_log_level log_level,
	size_t *coder_id,
	char *str
) {
	int				result;
	struct timeval	current_tv;
	size_t			curr_usec_delta;

	gettimeofday(&current_tv, NULL);
	curr_usec_delta = ctx->timestamp_start - ctx->tv.tv_usec;
	result = FAILURE;
	if (log_level < LOG_LEVEL)
		return (result);
	if (ctx)
		pthread_mutex_lock(&ctx->logging_mutex);
	if (
		(coder_id && printf("%ld %zu %s\n", curr_usec_delta, *coder_id, str) > 0)
		|| (printf("%ld %s\n", curr_usec_delta, str) > 0)
	)
		result = SUCCESS;
	if (ctx)
		pthread_mutex_unlock(&ctx->logging_mutex);
	return (result);
}

int	ft_log_debug(
	t_shared_ctx *ctx,
	char *message,
	size_t *coder_id
) {
	return (ft_log(ctx, DEBUG, coder_id, message));
}

int	ft_log_info(
	t_shared_ctx *ctx,
	char *message,
	size_t *coder_id
) {
	return (ft_log(ctx, INFO, coder_id, message));
}

int	ft_log_warn(
	t_shared_ctx *ctx,
	char *message,
	size_t *coder_id
) {
	return (ft_log(ctx, WARN, coder_id, message));
}

int	ft_log_error(
	t_shared_ctx *ctx,
	char *message,
	size_t *coder_id
) {
	return (ft_log(ctx, ERROR, coder_id, message));
}
