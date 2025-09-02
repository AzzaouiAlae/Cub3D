/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:21:05 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:21:06 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "imgs.h"

t_data	*get_east_img(void)
{
	static int	i;
	static long	old_time;

	fps(true, E_FPS);
	return (get_wall_img(g_vars()->info.list_east, g_vars()->info.east, &i,
			&old_time));
}

t_data	*get_north_img(void)
{
	static int	i;
	static long	old_time;

	fps(true, N_FPS);
	return (get_wall_img(g_vars()->info.list_north, g_vars()->info.north, &i,
			&old_time));
}

t_data	*get_south_img(void)
{
	static int	i;
	static long	old_time;

	fps(true, S_FPS);
	return (get_wall_img(g_vars()->info.list_south, g_vars()->info.south, &i,
			&old_time));
}

t_data	*get_west_img(void)
{
	static int	i;
	static long	old_time;

	fps(true, W_FPS);
	return (get_wall_img(g_vars()->info.list_west, g_vars()->info.west, &i,
			&old_time));
}

t_data	*get_wall_img(t_list *list, t_data *data, int *i, long *old_time)
{
	t_data	**imgs;

	if (list)
		imgs = list->content;
	else
		return (data);
	if ((1e6 / fps(false, 0)) < (g_vars()->time - *old_time))
	{
		(*i)++;
		*old_time = g_vars()->time;
	}
	if (*i > list->count - 1)
		*i = 0;
	return (imgs[*i]);
}
