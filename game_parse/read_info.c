#include "game_parse.h"

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
	while (info->count < 8 && read(fd, &ch, 1) > 0)
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
	if (!ft_strncmp(line->content, "F ", 2) && !(flags & 16) && line->count > 8)
		return (16);
	if (!ft_strncmp(line->content, "C ", 2) && !(flags & 32) && line->count > 8)
		return (32);
	if (!ft_strncmp(line->content, "DO ", 3) && !(flags & 64) && line->count > 8)
		return (64);
	if (!ft_strncmp(line->content, "DC ", 3) && !(flags & 128) && line->count > 8)
		return (128);
	return (0);
}

int	check_info(t_list *info)
{
	unsigned char	flags;
	int		i;
	t_str	**lines;
	int		result;

	if (info->count != 8)
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
