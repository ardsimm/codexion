/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <your@email.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:04:05 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:19:05 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLES_H
# define DONGLES_H

# include "headers/defines.h"

bool	can_take_dongle(t_coder *coder, t_dongle *dongle);

int		request_dongle(t_coder *coder, t_dongle *dongle);

int		take_dongle(t_coder *coder, t_dongle *dongle);

int		release_dongle(t_dongle *dongle);

void	dongles_free(t_dongle *dongles, size_t size);

#endif
