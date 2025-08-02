/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:29:29 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/08/02 13:38:10 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*g_mlx;
void	*g_win;
t_list	*g_map;
t_info	g_info;
t_data  g_win_img;
int g_width;
int g_height;
t_player g_player;

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
	data->img = mlx_xpm_file_to_image(g_mlx, relative_path,
			&(data->img_width), &(data->img_height));
	if (!(data->img))
		return NULL;
	save_img(data->img);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	return (data);
}
