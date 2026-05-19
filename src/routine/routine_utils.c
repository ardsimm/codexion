/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:37:00 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 15:38:21 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

bool	should_keep_running(t_shared_ctx shared)
{
	bool	run;

	pthread_mutex_lock(&shared.run_mutex);
	run = shared.run;
	pthread_mutex_unlock(&shared.run_mutex);
	return (run);
}
