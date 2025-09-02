/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:20:39 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:20:40 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMGS_H
# define IMGS_H
# include "../cub3d.h"

# define FPS 30
# define E_FPS 10
# define N_FPS 10
# define S_FPS 10
# define W_FPS 10
# define O_FPS 25
# define C_FPS 25

t_data	*get_east_img(void);
t_data	*get_north_img(void);
t_data	*get_south_img(void);
t_data	*get_west_img(void);
t_data	*get_open_door_img(void);
t_data	*get_close_door_img(void);
t_data	*get_wall_img(t_list *list, t_data *data, int *i, long *old_time);
int		fps(bool set, int fps);
t_data	*get_img(t_side side, t_side type);

#endif
