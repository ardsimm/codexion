/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:07:25 by smenard           #+#    #+#             */
/*   Updated: 2026/05/05 12:43:25 by smenard          ###   ########.fr       */
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
int				ft_log_debug(
					t_simulation *simulation,
					char *message,
					size_t *coder_id
					);
int				ft_log_info(
					t_simulation *simulation,
					char *message,
					size_t *coder_id
					);
int				ft_log_warn(
					t_simulation *simulation,
					char *message,
					size_t *coder_id
					);
int				ft_log_error(
					t_simulation *simulation,
					char *message,
					size_t *coder_id
					);

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

t_heap_queue	*heap_queue_init(size_t initial_size, size_t el_size);
void			heap_queue_add(t_heap_queue *queue, void *data);
void			*heap_queue_pop(t_heap_queue *hp);
void			*heap_queue_peek(t_heap_queue *hp);
void			heap_queue_clear(t_heap_queue *hp);

/* parsing/parse.c */
/**
 * Parsing & validation of program arguments
 */
t_simulation	*parse(int ac, char **av);

/* parsing/parse_validate.c */
/**
 * Validation of program arguments
 */
bool			validate_simulation(t_simulation *sim);

/* utils.c */
/**
 * Generic utils functions
 */
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strcpy(char *s1);
void			free_all(void **ptrs, size_t ptrs_len);
void			*free_return(void **ptrs, size_t ptrs_len, void *value);
int				free_return_int(void **ptrs, size_t ptrs_len, int value);

#endif