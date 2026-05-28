/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_lib.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:29:21 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:30:23 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_LIB_H
# define CODERS_LIB_H

# include "headers/lib.h"

/* tasks.c */
void	compile(t_coder *self);
void	debug(t_coder *self);
void	refactor(t_coder *self);

/* routine.c */
bool	should_continue(t_shared_ctx *shared);

#endif
