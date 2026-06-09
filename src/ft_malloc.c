/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_fail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vquetier <vquetier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:13:42 by vquetier          #+#    #+#             */
/*   Updated: 2026/01/31 14:38:11 by vquetier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef malloc
# undef malloc
#endif

#ifndef FAIL
# define FAIL 10
#endif

#include <stdlib.h>

void	*ft_malloc(size_t size)
{
	static int	i;

	i++;
	if (i == FAIL)
		return (NULL);
	return (malloc(size));
}
