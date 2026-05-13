/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_queue.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:53:00 by smenard           #+#    #+#             */
/*   Updated: 2026/05/13 12:03:48 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_QUEUE_H
# define HEAP_QUEUE_H

 t_heap_queue	*hq_init(size_t initial_size, size_t el_size,
		int (*get_score)(void *el));

void	hq_add(t_heap_queue *hq, void *data);

void	*hq_pop(t_heap_queue *hq);

#endif