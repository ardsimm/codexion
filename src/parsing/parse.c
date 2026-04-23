/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:58:53 by smenard           #+#    #+#             */
/*   Updated: 2026/04/23 19:19:25 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	parse_int_value(size_t *ptr, char *value)
{
	if (!validate_int_value(value))
		return (FAILURE);
	*ptr = atoi(value);
	if ((int64_t *) *ptr < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_str_value(char **ptr, char *value)
{
	if (strlen(value) == 0)
		return (FAILURE);
	if (strcmp("FIFO", value) || strcmp("EDF", value))
		return (FAILURE);
	*ptr = ft_strcpy(value);
	return (SUCCESS);
}

const t_simulation	*parse(int ac, char **av)
{
	(void) ac;
	(void) av;
	return (NULL);
}
