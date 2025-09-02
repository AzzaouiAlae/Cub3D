/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_game.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:54:18 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:54:19 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_GAME_H
# define MAP_GAME_H
# include "../cub3d.h"

typedef enum e_pos_type
{
	e_invalid,
	e_space,
	e_empty,
	e_wall,
	e_opened_gate,
	e_closed_gate
}				t_pos_type;

typedef struct s_map_data
{
	t_line		map_pos;
	t_point		start;
	t_pos_type	pos_type;
	int			y;
	int			x;
	int			color;
}				t_map_data;

void			map_game(void);
t_pos_type		check_pos(double x, double y);
void			init_map_pos(t_line *map_pos, t_point *start);
#endif
