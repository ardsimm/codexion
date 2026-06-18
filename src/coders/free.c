/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 12:48:50 by smenard           #+#    #+#             */
/*   Updated: 2026/06/18 12:49:09 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static void	free_coder(t_coder *coder)
{
	pthread_mutex_destroy(&coder->mutex);
}

void	coders_free(t_coder *coders, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free_coder(&coders[i++]);
}
