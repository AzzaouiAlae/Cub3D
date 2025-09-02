/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:12:07 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 23:12:08 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# include "list/list.h"
# include <stdbool.h>

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;
}				t_data;

typedef struct s_info
{
	t_data		*north;
	t_data		*south;
	t_data		*west;
	t_data		*east;
	t_data		*close_door;
	t_data		*open_door;
	t_list		*list_north;
	t_list		*list_south;
	t_list		*list_west;
	t_list		*list_east;
	t_list		*list_close_door;
	t_list		*list_open_door;
	int			floor_color;
	int			ceil_color;
}				t_info;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_player
{
	t_point		pixl_pos;
	t_point		map_pos;
	double		angle;
	double		move_speed;
	double		turn_speed;

}				t_player;

typedef struct s_pressed_keys
{
	char		w;
	char		s;
	char		a;
	char		d;
	char		left;
	char		right;
	char		o;
	bool		mouse;
}				t_keys;

typedef struct s_door
{
	int			row;
	int			col;
	double		dist;
}				t_door;

typedef struct s_global_vars
{
	t_list		*map;
	void		*mlx;
	void		*win;
	t_info		info;
	t_data		win_img;
	double		width;
	double		height;
	t_player	player;
	t_keys		keys;
	t_data		map_img;
	size_t		time;
	size_t		old_time;
	bool		gate_video;
}				t_global_vars;

#endif
