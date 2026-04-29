/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 13:50:32 by smenard           #+#    #+#             */
/*   Updated: 2026/04/29 15:13:10 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

bool	validate_scheduler(char *value)
{
	return (
		value != NULL
		&& (
			!strcmp(value, "EDF")
			|| !strcmp(value, "FIFO")
		)
	);
}

bool	validate_int_value(int value)
{
	return (value >= 0);
}

bool	validate_value(t_typed_voidp value)
{
	if (value.type == INT)
		return (validate_int_value(*(int *)value.data));
	else
		return (validate_scheduler(*(char **)value.data));
}
