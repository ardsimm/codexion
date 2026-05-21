/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:18:15 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:18:40 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include <pthread.h>

void	dongle_free(t_dongle *dongle)
{
	hq_free(dongle->hq.data);
	pthread_mutex_destroy(&dongle->hq.mutex);
}
