/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:20:03 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:20:17 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_parse.h"

int	set_color(char *clr, char *str)
{
	int	error;
	int	num;

	error = 0;
	num = ft_atoi(str, &error);
	if (error || num > 255)
		return (false);
	*clr = num;
	return (true);
}

bool	set_colors(char *str, int *color)
{
	char	*clr;
	char	**strs;
	int		len;

	if (ft_count_char(str, ',') != 2)
		return (false);
	clr = (char *)color;
	strs = ft_super_split(str, ",", "");
	len = ft_strslen(strs);
	if (len != 3)
		return (false);
	if (set_color(&(clr[2]), strs[0]) == false)
		return (false);
	if (set_color(&(clr[1]), strs[1]) == false)
		return (false);
	if (set_color(&(clr[0]), strs[2]) == false)
		return (false);
	return (true);
}

bool	set_img(char *str, t_data **img)
{
	*img = create_image(str);
	if (*img == NULL)
		return (false);
	return (true);
}

bool	parce_single_img(char **strs, t_info *info)
{
	if (!ft_strncmp(strs[0], "NO", 3))
		return (set_img(strs[1], &(info->north)));
	else if (!ft_strncmp(strs[0], "SO", 3))
		return (set_img(strs[1], &(info->south)));
	else if (!ft_strncmp(strs[0], "WE", 3))
		return (set_img(strs[1], &(info->west)));
	else if (!ft_strncmp(strs[0], "EA", 3))
		return (set_img(strs[1], &(info->east)));
	else if (!ft_strncmp(strs[0], "DO", 3))
		return (set_img(strs[1], &(info->open_door)));
	else if (!ft_strncmp(strs[0], "DC", 3))
		return (set_img(strs[1], &(info->close_door)));
	if (!ft_strncmp(strs[0], "F", 2))
		return (set_colors(strs[1], &(info->floor_color)));
	if (!ft_strncmp(strs[0], "C", 2))
		return (set_colors(strs[1], &(info->ceil_color)));
	return (false);
}

bool	try_parse_info(t_list *str_info, t_info *info)
{
	int		i;
	char	**strs;
	t_str	**lines;

	i = 0;
	lines = str_info->content;
	while (lines[i])
	{
		strs = ft_super_split(lines[i]->content, " ", "");
		if (file_extension(strs[1], ".xpm"))
		{
			if (parce_single_img(strs, info) == false)
				return (false);
		}
		else
		{
			if (parce_img_list(strs, info) == false)
				return (false);
		}
		i++;
	}
	return (true);
}
