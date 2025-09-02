/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:51:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 17:51:52 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "../cub3d.h"

t_end_point	raycaster(t_point start, double angle);
void		cast_all_rays(void);
void		draw_player_dir(double angle, double dir_dist, t_point start);

#endif
