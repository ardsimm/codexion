/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:06:38 by smenard           #+#    #+#             */
/*   Updated: 2026/04/29 17:52:15 by smenard          ###   ########.fr       */
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
