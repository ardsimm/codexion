/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:19:58 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:25:56 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_LIB_H
# define INIT_LIB_H

# include "headers/defines.h"

/* coders.c */
void	init_coder(int32_t i, t_ctx *ctx);

/* dongles.c */
int		init_dongle(uint32_t i, t_ctx *ctx);

/* ctx.c */
int		init_ctx(t_ctx *ctx);

#endif
