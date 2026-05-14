/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:53:16 by smenard           #+#    #+#             */
/*   Updated: 2026/05/14 16:42:34 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

int	ft_log_debug(
		t_shared_ctx *ctx,
		char *message,
		size_t *coder_id
		);

int	ft_log_info(
		t_shared_ctx *ctx,
		char *message,
		size_t *coder_id
		);

int	ft_log_warn(
		t_shared_ctx *ctx,
		char *message,
		size_t *coder_id
		);

int	ft_log_error(
		t_shared_ctx *ctx,
		char *message,
		size_t *coder_id
		);

#endif