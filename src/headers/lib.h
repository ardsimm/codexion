/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:25 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 19:13:11 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "includes.h"
# include "defines.h"

/* logging.c */
void				*ft_log_debug(char *message, size_t *coder_id);
void				*ft_log_info(char *message, size_t *coder_id);
void				*ft_log_warm(char *message, size_t *coder_id);
void				*ft_log_error(char *message, size_t *coder_id);

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

/* parse_validate.c */
bool				validate_int_value(char *value);

/* parse_free.c */
void				*free_return(t_simulation *simulation, void *value);

/* utils.c */
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strcpy(char *s1);

#endif