/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:44:54 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/28 19:09:58 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"
#include "../cub3d.h"

void	ft_exit(int num)
{
	ft_destroy_all();
	mlx_destroy_image(g_mlx, g_win_img.img);
	mlx_destroy_image(g_mlx, g_map_img.img);
	mlx_destroy_window(g_mlx, g_win);
	mlx_destroy_display(g_mlx);
	exit_clear_vlc();
	free(g_mlx);
	ft_free_all();
	exit(num);
}

void	*current_working_mem(void *mem, int set_to_null)
{
	static void	*working_mem;

	if (set_to_null)
		working_mem = NULL;
	if (mem)
		working_mem = mem;
	return (working_mem);
}
