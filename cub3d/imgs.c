/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 22:29:29 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/07/31 21:52:08 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	{
		ft_putstr_fd(2, "Error\ncreate image ", 19);
		ft_putstr_fd(2, relative_path, 0);
		ft_putstr_fd(2, "\n", 1);
		ft_exit(1);
	}
	save_img(data->img);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
	return (data);
}
