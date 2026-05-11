/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:05:02 by smenard           #+#    #+#             */
/*   Updated: 2026/05/12 17:23:35 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_log(
	pthread_mutex_t *logging_mutex,
	t_log_level log_level,
	size_t *coder_id,
	char *str
) {
	const char		*log_level_strs[4] = {[DEBUG] = "DEBUG", [INFO] = "INFO",
	[WARN] = "WARN", [ERROR] = "ERROR"};
	int				result;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	result = FAILURE;
	if (log_level < LOG_LEVEL)
		return (result);
	if (logging_mutex)
		pthread_mutex_lock(logging_mutex);
	if (
		(coder_id && printf("[%s|%ld|%zu] %s\n", log_level_strs[log_level],
				tv.tv_usec, *coder_id, str) > 0)
		|| (printf("[%s|%ld] %s\n", log_level_strs[log_level],
				tv.tv_usec, str) > 0)
	)
		result = SUCCESS;
	if (logging_mutex)
		pthread_mutex_unlock(logging_mutex);
	return (result);
}

int	ft_log_debug(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
) {
	return (ft_log(logging_mutex, DEBUG, coder_id, message));
}

int	ft_log_info(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
) {
	return (ft_log(logging_mutex, INFO, coder_id, message));
}

int	ft_log_warn(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
) {
	return (ft_log(logging_mutex, WARN, coder_id, message));
}

int	ft_log_error(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
) {
	return (ft_log(logging_mutex, ERROR, coder_id, message));
}
