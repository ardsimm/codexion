/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 11:59:51 by smenard           #+#    #+#             */
/*   Updated: 2026/06/18 12:38:54 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include "headers/defines.h"

/* routine.c */
void	*coder_routine(void *data);

/* free.c */
void	coders_free(t_coder *coders, size_t size);
#endif
