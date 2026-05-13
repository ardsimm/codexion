/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:53:16 by smenard           #+#    #+#             */
/*   Updated: 2026/05/13 11:58:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

int	ft_log_debug(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
);

int	ft_log_info(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
);

int	ft_log_warn(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
);

int	ft_log_error(
	pthread_mutex_t *logging_mutex,
	char *message,
	size_t *coder_id
);


#endif