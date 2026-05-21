/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:20:03 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 17:26:03 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"
#include "init/headers/init_lib.h"

int	init(t_ctx *ctx)
{
	uint32_t	i;

	if (init_ctx(ctx) == FAILURE)
		return (FAILURE);
	i = 0;
	while (i < ctx->coders_count)
		init_dongle(i++, ctx);
	i = 0;
	while (i < ctx->coders_count)
		init_coder(i++, ctx);
	return (SUCCESS);
}
