/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:58:53 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 16:12:04 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/parsing_lib.h"
#include "headers/lib.h"

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
	if (val > INT32_MAX || (int)val < 0)
		return (-1);
	return (val);
}

static void	build_simulation_ptrs_array(t_typed_voidp ptrs[EXPECTED_AC],
		t_ctx *ctx)
{
	ptrs[0] = (t_typed_voidp){.type = INT, .data = &ctx->coders_count};
	ptrs[1] = (t_typed_voidp){.type = INT,
		.data = &ctx->shared.time_to_burnout};
	ptrs[2] = (t_typed_voidp){.type = INT,
		.data = &ctx->shared.time_to_compile};
	ptrs[3] = (t_typed_voidp){.type = INT, .data = &ctx->shared.time_to_debug};
	ptrs[4] = (t_typed_voidp){.type = INT,
		.data = &ctx->shared.time_to_refactor};
	ptrs[5] = (t_typed_voidp){.type = INT,
		.data = &ctx->shared.number_of_compiles};
	ptrs[6] = (t_typed_voidp){.type = INT,
		.data = &ctx->shared.number_of_compiles};
	ptrs[7] = (t_typed_voidp){.type = STR, .data = &ctx->scheduler};
}

t_ctx	*parse(int ac, char **av)
{
	size_t			i;
	t_ctx			*ctx;
	t_typed_voidp	ptrs[EXPECTED_AC];

	ctx = ft_calloc(1, sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	build_simulation_ptrs_array(ptrs, ctx);
	i = 1;
	if (ac < EXPECTED_AC)
		return (free_return((void *[]){ctx}, 1, NULL));
	while (i < (size_t)ac)
	{
		if (ptrs[i - 1].type == INT)
			*(int *)ptrs[i - 1].data = atoi_safe(av[i]);
		else if (!strcmp(av[i], "FIFO"))
			*(t_scheduler_mode *)ptrs[i - 1].data = FIFO;
		else if (!strcmp(av[i], "EDF"))
			*(t_scheduler_mode *)ptrs[i - 1].data = EDF;
		else
			*(t_scheduler_mode *)ptrs[i - 1].data = INVALID;
		i++;
	}
	if (!validate_ctx(ctx))
		return ((free_return((void *[]){ctx}, 2, NULL)));
	return (ctx);
}
