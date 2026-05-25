/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:04:07 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 17:07:12 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

size_t	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((size_t)tv.tv_sec * 1000000) + ((size_t)tv.tv_usec));
}
