/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:46:14 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 14:49:32 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include "headers/defines.h"

/* getters.c */
size_t	get_size_t_value(size_t *ptr, pthread_mutex_t *mutex);

bool	get_bool_value(bool *ptr, pthread_mutex_t *mutex);

/* setters.c */
void	set_size_t_value(size_t *ptr, size_t value, pthread_mutex_t *mutex);

void	set_bool_value(bool *ptr, bool value, pthread_mutex_t *mutex);

#endif
