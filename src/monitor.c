/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:03:38 by smenard           #+#    #+#             */
/*   Updated: 2026/05/12 17:23:57 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	*routine_de_con(void *param)
{
	t_coder	*self;

	self = (t_coder*) param;
	for (int i = 0; i < 12; i++)
	{
		ft_log_debug(self->logging_mutex, "dummy routine", &self->id);
		usleep(50);
	}
	self->done = true;
	return (NULL);
}

void	*monitor_simulation(t_simulation *sim)
{
	pthread_t	*threads;
	void		**ret;
	bool		done;
	size_t		i;

	ret = ft_calloc(1, sizeof(void*));
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
	return (NULL);
}
