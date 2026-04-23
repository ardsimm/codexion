/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:25 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 16:16:26 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "includes.h"
# include "defines.h"

/* logging.c */
void				*ft_log_debug(char *message);
void				*ft_log_info(char *message);
void				*ft_log_error(char *message);

/* routine.c */
void				*coder_routine(void *data);

/* simulation.c */
void				*run_simulation(t_simulation *simulation);

/* heap_queue.c */
t_heap_queue		*heap_queue_create(size_t initial_size, size_t el_size);
void				heap_queue_add(t_heap_queue *queue, void *data);
void				*heap_queue_remove(t_heap_queue *queue, void *data);
void				*heap_queue_pop(t_heap_queue *queue);
void				*heap_queue_clear(t_heap_queue *queue);

/* parse.c */
const t_simulation	*parse(int ac, char **av);

/* utils.c */
void				*ft_calloc(size_t nmemb, size_t size);

#endif