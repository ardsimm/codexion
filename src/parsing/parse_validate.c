/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:27:19 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 19:09:05 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

bool	validate_int_value(char *value)
{
	size_t	i;

	i = 0;
	while (value[i])
	{
		if (value[i] < '0' || value[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (true);
}
