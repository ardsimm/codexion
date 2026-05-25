/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:25:34 by smenard           #+#    #+#             */
/*   Updated: 2026/05/25 16:26:57 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

bool	hq_contains(t_heap_queue *hq, void *data)
{
	size_t	i;

	i = 0;
	while (i < hq->size)
	{
		if (hq->data[i++].data == data)
			return (true);
	}
	return (false);
}
