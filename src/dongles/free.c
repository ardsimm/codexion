/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:18:15 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 16:28:45 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static void	dongle_free(t_dongle *dongle)
{
	hq_free(dongle->hq);
	pthread_mutex_destroy(&dongle->mutex);
}

void	dongles_free(t_dongle *dongles, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		dongle_free(&(dongles[i++]));
}
