/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:25 by smenard           #+#    #+#             */
/*   Updated: 2026/04/29 15:28:15 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "defines.h"
# include "includes.h"

/* logging.c */
/**
 * Logger functions with different log levels
 */
void			*ft_log_debug(char *message, size_t *coder_id);
void			*ft_log_info(char *message, size_t *coder_id);
void			*ft_log_warm(char *message, size_t *coder_id);
void			*ft_log_error(char *message, size_t *coder_id);

/* routine.c */
/**
 * Routine of the coders (threads)
 */
void			*coder_routine(void *data);

/* simulation.c */
/**
 * Main simulation loop
 */
void			*run_simulation(t_simulation *simulation);

/* heap_queue.c */
/**
 * Heap queue sources
 */
t_heap_queue	*heap_queue_create(size_t initial_size, size_t el_size);
void			heap_queue_add(t_heap_queue *queue, void *data);
void			*heap_queue_remove(t_heap_queue *queue, void *data);
void			*heap_queue_pop(t_heap_queue *queue);
void			*heap_queue_clear(t_heap_queue *queue);

/* parsing/parse.c */
/**
 * Parsing & validation of program arguments
 */
t_simulation	*parse(int ac, char **av);

/* parsing/parse_validate.c */
/**
 * Validation of program arguments
 */
bool			validate_value(t_typed_voidp value);

/* utils.c */
/**
 * Generic utils functions
 */
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strcpy(char *s1);
void			*free_return(void **ptrs, size_t ptrs_len, void *value);

#endif