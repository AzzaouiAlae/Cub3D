/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:02:47 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/01 16:55:51 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_parse.h"

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

t_game_map_status	game_parse(char *filename, t_info *info)
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
	if (check_info(str_info) != 255)
		return err_invalid_info;
	if (try_parse_info(str_info, info) == false)
		return err_invalid_info;
	if (read_map(g_map, fd) == false)
		return err_invalid_map;
	if (check_map(g_map, &g_player) == false)
		return err_invalid_map;
	return ok;
}
