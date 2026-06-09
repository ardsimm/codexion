/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smenard <smenard@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 14:39:51 by smenard           #+#    #+#             */
/*   Updated: 2026/05/29 14:41:57 by smenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lib.h"

t_dongle	*get_first_dongle(t_coder *coder)
{
	if (coder->dongle_left->id < coder->dongle_right->id)
		return (coder->dongle_left);
	return (coder->dongle_right);
}

t_dongle	*get_second_dongle(t_coder *coder)
{
	if (coder->dongle_left->id < coder->dongle_right->id)
		return (coder->dongle_right);
	return (coder->dongle_left);
}
