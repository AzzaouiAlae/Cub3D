/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:02:47 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/08/02 18:04:20 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_map.h"

int	file_extension(char *filename, char *extension)
{
	int	file_len;
	int	ext_len;
	int	i;

	if (!filename)
		return (0);
	file_len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (0);
	i = file_len - ext_len;
	return (!ft_strncmp(&(filename[i]), extension, ext_len + 1));
}

void	read_info(int fd, t_list *info)
{
	t_str	*line;
	char	ch;

	line = str_new();
	while (info->count < 6 && read(fd, &ch, 1) > 0)
	{
		if (line->count == 0 && ch == '\n')
			continue ;
		if (line->count > 0 && ch == '\n')
		{
			list_add(info, (long)line);
			line = str_new();
		}
		else
			str_add_char(line, ch);
	}
	if (line->count > 0)
		list_add(info, (long)line);
}

int	choose_flag(t_str *line, char flags)
{
	if (!ft_strncmp(line->content, "NO ", 3) && !(flags & 1) && line->count > 3)
		return (1);
	if (!ft_strncmp(line->content, "SO ", 3) && !(flags & 2) && line->count > 3)
		return (2);
	if (!ft_strncmp(line->content, "WE ", 3) && !(flags & 4) && line->count > 3)
		return (4);
	if (!ft_strncmp(line->content, "EA ", 3) && !(flags & 8) && line->count > 3)
		return (8);
	if (!ft_strncmp(line->content, "F ", 2) && !(flags & 16) && line->count > 6)
		return (16);
	if (!ft_strncmp(line->content, "C ", 2) && !(flags & 32) && line->count > 6)
		return (32);
	return (0);
}

int	check_info(t_list *info)
{
	char	flags;
	int		i;
	t_str	**lines;
	int		result;

	if (info->count != 6)
		return (0);
	flags = 0;
	i = 0;
	lines = info->content;
	while (lines[i])
	{
		result = choose_flag(lines[i], flags);
		if (!result)
			return (0);
		flags += result;
		i++;
	}
	return (flags);
}

int	set_color(char *clr, char *str)
{
	int	error;
	int	num;

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

	clr = (char *)color;
	strs = ft_super_split(str, ",", "");
	len = ft_strslen(strs);
	if (len != 3)
		return (false);
	if (set_color(&(clr[2]), strs[2]) == false)
		return false;
	if (set_color(&(clr[1]), strs[1]) == false)
		return false;
	if (set_color(&(clr[0]), strs[0]) == false)
		return false;
	return true;
}

bool	set_img(char *str, t_data **img)
{
	*img = create_image(str);
	if (*img == NULL)
		return false;
	return true;
}

bool	try_set_info(char **strs, t_info *info)
{
	if (!ft_strncmp(strs[0], "NO", 3))
		return set_img(strs[1], &(info->north));
	else if (!ft_strncmp(strs[0], "SO", 3))
		return set_img(strs[1], &(info->south));
	else if (!ft_strncmp(strs[0], "WE", 3))
		return set_img(strs[1], &(info->west));
	else if (!ft_strncmp(strs[0], "EA", 3))
		return set_img(strs[1], &(info->east));
	if (!ft_strncmp(strs[0], "F", 2))
		return set_colors(strs[1], &(info->floor_color));
	if (!ft_strncmp(strs[0], "C", 2))
		return set_colors(strs[1], &(info->ceil_color));
	return false;
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
		if (try_set_info(strs, info) == false)
			return false;
		i++;
	}
	return true;
}

t_str	*read_line(int fd, int skip_empty_line)
{
	t_str	*line;
	char	ch;

	line = str_new();
	while (read(fd, &ch, 1) > 0)
	{
		if (skip_empty_line && ch == '\n' && line->count == 0)
			continue ;
		if (ch == '\n')
			break ;
		str_add_char(line, ch);
	}
	return line;
}

bool	read_map(t_list *map, int fd)
{
	t_str	*line;

	line = read_line(fd, 1);
	if (line->count == 0)
		return false;
	list_add(map, (long)line);
	while (1)
	{
		line = read_line(fd, 0);
		if (line->count == 0)
			break ;
		list_add(map, (long)line);
	}
	line = read_line(fd, 1);
	if (line->count || map->count < 3)
		return false;
	return true;
}

bool	check_map_tail(t_list *map, t_str **lines, int i, int j)
{
	int	max_hiegh;
	int	max_width;

	max_hiegh = map->count - 1;
	max_width = lines[i]->count - 1;
	if (i == 0 || max_hiegh <= i || j == 0 || max_width <= j)
		return false;
	if (lines[i]->content[j + 1] == ' ' || lines[i]->content[j - 1] == ' ')
		return false;
	if (lines[i - 1]->count - 1 < j || lines[i + 1]->count - 1 < j)
		return false;
	if (lines[i - 1]->content[j] == ' ' || lines[i + 1]->content[j] == ' ')
		return false;
	return true;
}
void init_player(t_player *player, char ch)
{
	if (ch == 'N')
		player->angle = 90;
	else if (ch == 'S')
		player->angle = 270;
	else if (ch == 'E')
		player->angle = 0;
	else if (ch == 'W')
		player->angle = 180;
	player->pos.x = player->map_pos.x * M_M_TIAL_SIZE + ((float)M_M_TIAL_SIZE / 2);
	player->pos.y = player->map_pos.y * M_M_TIAL_SIZE + ((float)M_M_TIAL_SIZE / 2);
}
bool	check_map(t_list *map, t_player *player)
{
	int		i;
	int		j;
	t_str	**lines;

	i = 0;
	lines = map->content;
	while (lines[i])
	{
		//check invalid char
		j = 0;
		while (lines[i]->count > j)
		{
			if (ft_strchr("0NSEW", lines[i]->content[j]) &&
					!check_map_tail(map, lines, i, j))
				return false;
			if (ft_strchr("NSEW", lines[i]->content[j]))
			{
				player->map_pos.x = j;
				player->map_pos.y = i;
				init_player(player, lines[i]->content[j]);
			}
			j++;
		}
		i++;
	}
	return true;
}

t_game_map_status	game_map(char *filename, t_info *info)
{
	int		fd;
	t_list	*str_info;

	str_info = list_new(sizeof(t_str *));
	if (!file_extension(filename, ".cub"))
		return err_file_extension;
	fd = ft_open(filename, O_RDONLY, 0666);
	if (fd == -1)
		return err_open_file;
	read_info(fd, str_info);
	if (check_info(str_info) != 63)
		return err_invalid_info;
	if (try_parse_info(str_info, info) == false)
		return err_invalid_info;
	if (read_map(g_map, fd) == false)
		return err_invalid_map;
	if (check_map(g_map, &g_player) == false)
		return err_invalid_map;
	return ok;
}
