/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:51:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 18:41:10 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "../cub3d.h"

t_end_point	raycaster(t_point start, double angle);
void		cast_all_rays(void);
void		draw_player_dir(double angle, double dir_dist, t_point start);
double	my_cos(float alpha);
double	my_tan(double angle, char inter);
bool	in_range(double start, double end, double num);
bool	is_valid_ray(int x, int y);
int	darkness_effect(int color, double dist);
int	darkness_effect_ceil(int color, double dist);
int	darkness_effect_floor(int color, double dist);
void	draw_line(int x, int y, int l, t_point img_start, double orginal_l,
		t_end_point p);
void	render_walls(t_end_point p, int i);
t_data	*get_img(t_side side, t_side type);

#endif
