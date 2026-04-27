/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:58:53 by smenard           #+#    #+#             */
/*   Updated: 2026/04/27 17:32:08 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static bool	ft_isspace(char c)
{
	return ((c <= '\r' && c >= '\t') || c == ' ');
}

static bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	atoi_safe(char *value)
{
	size_t		i;
	uint64_t	val;

	i = 0;
	val = 0;
	while (ft_isspace(value[i]))
		i++;
	while (ft_isdigit(value[i]) || value[i] == '-')
	{
		if (value[i] == '-')
			return (-1);
		val *= 10;
		val += value[i] - '0';
		i++;
	}
	printf("Val in atoi_safe: %zu\n", val);
	if (val > INT32_MAX || (int) val < 0)
		return (-1);
	return (val);
}

static void	build_simulation_ptrs_array(
	void *ptrs[EXPECTED_AC],
	t_simulation *simulation
) {
	ptrs[0] = &simulation->coders_count;
	ptrs[1] = &simulation->time_to_burnout;
	ptrs[2] = &simulation->time_to_compile;
	ptrs[3] = &simulation->time_to_debug;
	ptrs[4] = &simulation->time_to_refactor;
	ptrs[5] = &simulation->number_of_compiles;
	ptrs[6] = &simulation->dongle_cooldown;
	ptrs[7] = &simulation->scheduler;
}

t_simulation	*parse(int ac, char **av)
{
	size_t			i;
	t_simulation	*simulation;
	void			*ptrs[EXPECTED_AC];

	simulation = ft_calloc(1, sizeof(t_simulation));
	build_simulation_ptrs_array(ptrs, simulation);
	i = 1;
	if (ac < EXPECTED_AC)
		return (NULL);
	while (i <= EXPECTED_AC)
	{
		if (i < EXPECTED_AC)
		{
			int v = atoi_safe(av[i]);
			*(size_t *)ptrs[i - 1] = v;
		}

		else
			*(char **)ptrs[i - 1] = ft_strcpy(av[i]);
		if ((i < EXPECTED_AC && *(size_t *)ptrs[i - 1] < 0)
			|| (i == EXPECTED_AC && (ptrs[i - 1] == NULL
				|| strcmp(*(char **)ptrs[i - 1], "FIFO")
				|| strcmp(*(char **)ptrs[i - 1], "EDF"))))
			return (free_return((void *[]){simulation->scheduler, simulation},
				2, NULL));
		i++;
	}
	return (simulation);
}
