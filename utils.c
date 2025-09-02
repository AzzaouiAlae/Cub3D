/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:48:15 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 16:48:34 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "game_parse/game_parse.h"
#include "map_game/map_game.h"
#include "raycasting/raycasting.h"

size_t	get_curr_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)(time.tv_sec * 1000000 + time.tv_usec));
}

void	normalize_angle(double *angle)
{
	if (*angle < 0.0)
		*angle += 360.0;
	else if (*angle > 360.0)
		*angle -= 360.0;
}

void	my_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_get_pixel(t_data *data, int x, int y)
{
	char	*dst;

	if (!data || !data->addr)
		return (0);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*((unsigned int *)dst));
}

t_data	*create_image(char *relative_path)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->img = mlx_xpm_file_to_image(g_mlx, relative_path, &(data->img_width),
			&(data->img_height));
	if (!(data->img))
		return (NULL);
	save_img(data->img);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	return (data);
}
