/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:01:52 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 18:02:02 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	free_all(void **ptrs, size_t ptrs_len)
{
	size_t	i;

	i = 0;
	while (i < ptrs_len)
		free(ptrs[i++]);
}

void	*free_return(void **ptrs, size_t ptrs_len, void *value)
{
	free_all(ptrs, ptrs_len);
	return (value);
}

int	free_return_int(void **ptrs, size_t ptrs_len, int value)
{
	free_all(ptrs, ptrs_len);
	return (value);
}
