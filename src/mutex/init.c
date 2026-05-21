/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:30:50 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:45:05 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	init_voidp_mutex(t_voidp_mutex mutex, t_typed_voidp value)
{
	pthread_mutex_init(&mutex.mutex, NULL);
	mutex.data = value;
}

void	init_size_t_mutex(t_size_t_mutex mutex, size_t value)
{
	pthread_mutex_init(&mutex.mutex, NULL);
	mutex.data = value;
}

void	init_bool_mutex(t_bool_mutex mutex, bool value)
{
	pthread_mutex_init(&mutex.mutex, NULL);
	mutex.data = value;
}
