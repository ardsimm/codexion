/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:03:38 by smenard           #+#    #+#             */
/*   Updated: 2026/05/14 16:48:23 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

void	*routine_de_con(void *param)
{
	t_coder	*self;
	size_t	i;

	self = (t_coder *)param;
	i = 0;
	while (i < 12)
	{
		ft_log_debug(&self->shared, "dummy routine", &self->id);
		usleep(500);
		i++;
	}
	self->done = true;
	return (NULL);
}

void	*monitor_simulation(t_ctx *sim)
{
	pthread_t	*threads;
	void		**ret;
	bool		done;
	size_t		i;

	ret = ft_calloc(1, sizeof(void *));
	threads = ft_calloc(sim->coders_count, sizeof(pthread_t));
	done = false;
	i = 0;
	while (i < sim->coders_count)
	{
		pthread_create(&threads[i], NULL, routine_de_con, &sim->coders[i]);
		i++;
	}
	i = 0;
	while (i < sim->coders_count)
		pthread_join(threads[i++], ret);
	while (!done)
	{
		i = 0;
		while (i < sim->coders_count)
		{
			if (sim->coders[i].done)
				done = true;
			i++;
			usleep(10);
		}
	}
	free(ret);
	return (NULL);
}
