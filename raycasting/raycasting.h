/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:51:31 by aabouriz          #+#    #+#             */
/*   Updated: 2025/09/02 22:50:24 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "../cub3d.h"
# include "../imgs/imgs.h"

typedef struct s_draw_line
{
	int			x;
	int			y;
	int			length;
	t_point		img_start;
	double		orginal_l;
	t_end_point	p;
}				t_draw_line;

typedef struct s_raycaster
{
	double		dpr;
	double		angle;
	double		real_alpha;
	t_end_point	p;
	int			i;
	t_line		map_pos;
	t_point		start;
}				t_raycaster;

t_end_point		raycaster(t_point start, double angle);
void			cast_all_rays(void);
double			my_cos(float alpha);
double			my_tan(double angle, char inter);
bool			in_range(double start, double end, double num);
bool			is_valid_ray(int x, int y);
int				darkness_effect(int color, double dist);
int				darkness_effect_ceil(int color, double dist);
int				darkness_effect_floor(int color, double dist);
void			draw_line(t_draw_line data);
void			render_walls(t_end_point p, int i);
t_door			*door_info(void);
t_side			get_side(t_point p, t_point start, char inter, t_side *type);
void			reset_door_info(void);
void			check_door(t_point p, double dist);
void			draw_ceil(t_draw_line data);
void			draw_floor(t_draw_line data, int i);

#endif
