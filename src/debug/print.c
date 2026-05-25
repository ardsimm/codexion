/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 19:09:13 by smenard           #+#    #+#             */
/*   Updated: 2026/05/20 19:31:13 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

static void	print_heap_queue(t_heap_queue *hq, int indent)
{
	size_t	i;
	char	*pad;
	char	*pad2;

	if (!hq)
	{
		printf("null");
		return ;
	}
	pad = indent == 2 ? "    " : "      ";
	pad2 = indent == 2 ? "      " : "        ";
	printf("{\n");
	printf("%s\"size\": %zu,\n", pad, hq->size);
	printf("%s\"max_size\": %zu,\n", pad, hq->max_size);
	printf("%s\"data\": [", pad);
	i = 0;
	while (i < hq->size)
	{
		printf("\n%s{ \"key\": %zu }", pad2, hq->data[i].key);
		if (i + 1 < hq->size)
			printf(",");
		i++;
	}
	if (hq->size)
		printf("\n%s", pad);
	printf("]\n%s}", indent == 2 ? "  " : "    ");
}

static void	print_dongle(t_dongle *d, int idx)
{
	printf("    {\n");
	printf("      \"id\": %zu,\n", d->id);
	printf("      \"cooldown\": %zu,\n", d->cooldown);
	printf("      \"last_use_timestamp\": %zu,\n",
		d->last_use_timestamp);
	printf("      \"in_use\": %s,\n", d->in_use ? "true" : "false");
	printf("      \"hq\": ");
	print_heap_queue(d->hq, 3);
	printf("\n    }");
	(void)idx;
}

static void	print_shared_ctx(t_shared_ctx *s, int indent)
{
	char	*pad;

	pad = indent == 1 ? "  " : "    ";
	printf("{\n");
	printf("%s\"time_to_burnout\": %u,\n", pad, s->time_to_burnout);
	printf("%s\"time_to_compile\": %u,\n", pad, s->time_to_compile);
	printf("%s\"time_to_debug\": %u,\n", pad, s->time_to_debug);
	printf("%s\"time_to_refactor\": %u,\n", pad, s->time_to_refactor);
	printf("%s\"number_of_compiles\": %u,\n", pad, s->number_of_compiles);
	printf("%s\"dongle_cooldown\": %u,\n", pad, s->dongle_cooldown);
	printf("%s\"timestamp_start\": %zu,\n", pad, s->timestamp_start);
	printf("%s\"run\": %s\n", pad, s->run ? "true" : "false");
	printf("%s}", indent == 1 ? "" : "  ");
}

static void	print_coder(t_coder *c)
{
	printf("    {\n");
	printf("      \"id\": %zu,\n", c->id);
	printf("      \"last_compile_timestamp\": %zu,\n",
		c->last_compile_timestamp);
	printf("      \"done\": %s,\n",
		c->done ? "true" : "false");
	printf("      \"dongle_left\": %s,\n", c->dongle_left ? "{ ... }" : "null");
	printf("      \"dongle_right\": %s,\n",
		c->dongle_right ? "{ ... }" : "null");
	printf("      \"shared\": ");
	print_shared_ctx(c->shared, 2);
	printf("\n    }");
}

void	print_ctx(t_ctx *ctx)
{
	size_t	i;

	printf("{\n");
	printf("  \"coders_count\": %u,\n", ctx->coders_count);
	printf("  \"scheduler_mode\": %s\n",
		ctx->scheduler == FIFO ? "FIFO" : "EDF");
	printf("  \"dongles\": [\n");
	i = 0;
	while (i < ctx->coders_count)
	{
		print_dongle(&ctx->dongles[i], i);
		if (i + 1 < ctx->coders_count)
			printf(",");
		printf("\n");
		i++;
	}
	printf("  ],\n");
	printf("  \"coders\": [\n");
	i = 0;
	while (i < ctx->coders_count)
	{
		print_coder(&ctx->coders[i]);
		if (i + 1 < ctx->coders_count)
			printf(",");
		printf("\n");
		i++;
	}
	printf("  ],\n");
	printf("  \"shared\": ");
	print_shared_ctx(&ctx->shared, 1);
	printf("\n}\n");
}
