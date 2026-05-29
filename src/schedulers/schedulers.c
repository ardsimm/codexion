/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedulers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:22:23 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 15:17:57 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "utils/headers/utils.h"

size_t	get_key_fifo(void *el)
{
	(void)el;
	return (get_time_us());
}

size_t	get_key_edf(void *el)
{
	const t_coder	*coder = (const t_coder *)el;
	size_t			time_to_burnout;

	time_to_burnout = get_time_us() - coder->last_compile_timestamp
		+ coder->shared->time_to_burnout;
	return (time_to_burnout);
}
