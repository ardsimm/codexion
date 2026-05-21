/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:16:57 by smenard           #+#    #+#             */
/*   Updated: 2026/05/21 16:46:35 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
#define MUTEX_H

# include "headers/defines.h"

size_t			get_size_t_mutex(t_size_t_mutex mutex);

t_typed_voidp	get_voidp_mutex(t_voidp_mutex mutex);

bool			get_bool_mutex(t_bool_mutex mutex);

void			set_voidp_mutex(t_voidp_mutex mutex, t_typed_voidp data);

void			set_size_t_mutex(t_size_t_mutex mutex, size_t data);

void			set_bool_mutex(t_bool_mutex mutex, bool data);

void			init_voidp_mutex(t_voidp_mutex mutex, t_typed_voidp value);

void			init_size_t_mutex(t_size_t_mutex mutex, size_t value);

void			init_bool_mutex(t_bool_mutex mutex, bool value);

#endif
