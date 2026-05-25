/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:05:02 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 18:22:25 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

static int	ft_log(t_shared_ctx *ctx, t_log_level log_level, size_t *coder_id,
		char *str)
{
	int		result;
	size_t	curr_usec_delta;

	curr_usec_delta = get_time_ms() - ctx->timestamp_start;
	result = FAILURE;
	if (log_level < LOG_LEVEL)
		return (result);
	if (ctx)
		pthread_mutex_lock(&ctx->logging_active.mutex);
	if (coder_id)
	{
		if (printf("%ld %zu %s\n", curr_usec_delta, *coder_id, str))
			return (SUCCESS);
	}
	else if (printf("%ld %s\n", curr_usec_delta, str) > 0)
		return (SUCCESS);
	if (ctx)
		pthread_mutex_unlock(&ctx->logging_active.mutex);
	return (result);
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
