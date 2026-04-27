/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:06:38 by smenard           #+#    #+#             */
/*   Updated: 2026/04/27 17:32:45 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size * nmemb);
	return (ptr);
}

char	*ft_strcpy(char *s1)
{
	const size_t	len = strlen(s1);
	char			*s2;
	size_t			i;

	s2 = ft_calloc(len, sizeof(char));
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	*free_return(void **ptrs, size_t ptrs_len, void *value)
{
	size_t	i;

	i = 0;
	while (i < ptrs_len)
		free(ptrs[i++]);
	return (value);
}
