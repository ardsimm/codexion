/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:05:02 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 17:43:41 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*ft_log(t_log_level log_level, size_t *coder_id, char *str)
{
	(void) log_level;
	(void) coder_id;
	(void) str;
	return (EXIT_SUCCESS);
}

void	*ft_log_debug(char *message, size_t *coder_id)
{
	(void) message;
	return (NULL);
}

void	*ft_log_info(char *message, size_t *coder_id)
{
	(void) message;
	return (NULL);
}

void	*ft_log_warm(char *message, size_t *coder_id)
{
	(void) message;
	return (NULL);
}

void	*ft_log_error(char *message, size_t *coder_id)
{
	(void) message;
	return (NULL);
}
