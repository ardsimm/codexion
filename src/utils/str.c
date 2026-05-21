/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:01:04 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 18:01:18 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

char	*ft_strcpy(char *s1)
{
	const size_t	len = strlen(s1);
	char			*s2;
	size_t			i;

	if (len == 0)
		return (NULL);
	s2 = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
