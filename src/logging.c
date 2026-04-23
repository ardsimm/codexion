/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:05:02 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 17:22:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	*ft_log(char *prefix, char *str)
{
	(void) prefix;
	(void) str;
	return (EXIT_SUCCESS);
}

void	*ft_log_debug(char *message)
{
	(void) message;
	return (NULL);
}

void	*ft_log_info(char *message)
{
	(void) message;
	return (NULL);
}

void	*ft_log_error(char *message)
{
	(void) message;
	return (NULL);
}
