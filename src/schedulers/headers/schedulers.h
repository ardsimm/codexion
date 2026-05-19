/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedulers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:21:38 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 15:23:16 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULERS_H
# define SCHEDULERS_H

# include "headers/defines.h"

size_t	get_key_fifo(void *el);

size_t	update_key_fifo(t_heap_queue_item *item);

#endif

