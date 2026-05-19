/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_lib.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:18:35 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 15:39:05 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_LIB_H
# define ROUTINE_LIB_H

# include "headers/defines.h"

/* tasks.c */
void	compile(const t_coder *self);
void	debug(const t_coder *self);
void	refactor(const t_coder *self);

/* routine_utils.c */
bool	should_keep_running(t_shared_ctx shared);

#endif
