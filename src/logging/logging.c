/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:05:02 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 15:11:51 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static int	ft_log(t_shared_ctx *ctx, size_t *coder_id, char *str,
		t_logging_arguments args)
{
	size_t	curr_usec_delta;

	if (args.log_level < LOG_LEVEL)
		return (FAILURE);
	if (!ctx)
	{
		printf("%s\n", str);
		return (SUCCESS);
	}
	pthread_mutex_lock(&ctx->mutex);
	if (!ctx->run && coder_id && args.log_level == INFO)
	{
		pthread_mutex_unlock(&ctx->mutex);
		return (FAILURE);
	}
	pthread_mutex_lock(&ctx->logging_mutex);
	curr_usec_delta = (get_time_us() - ctx->timestamp_start) / 1000;
	if (coder_id)
		fprintf(args.print_f, "%ld %zu %s\n", curr_usec_delta, *coder_id, str);
	else
		fprintf(args.print_f, "%ld %s\n", curr_usec_delta, str);
	pthread_mutex_unlock(&ctx->logging_mutex);
	pthread_mutex_unlock(&ctx->mutex);
	return (SUCCESS);
}

int	ft_log_debug(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, coder_id, message,
			(t_logging_arguments){.log_level = DEBUG, .print_f = stdout}));
}

int	ft_log_info(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, coder_id, message,
			(t_logging_arguments){.log_level = INFO, .print_f = stdout}));
}

int	ft_log_warn(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, coder_id, message,
			(t_logging_arguments){.log_level = WARN, .print_f = stderr}));
}

int	ft_log_error(t_shared_ctx *ctx, char *message, size_t *coder_id)
{
	return (ft_log(ctx, coder_id, message,
			(t_logging_arguments){.log_level = ERROR, .print_f = stderr}));
}
