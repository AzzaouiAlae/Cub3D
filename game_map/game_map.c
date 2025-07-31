/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:02:47 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/07/31 23:35:32 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_map.h"

int file_extension(char *filename, char *extension)
{
    int file_len;
    int ext_len;
    int i;

    if (!filename)
        return 0;
    file_len = ft_strlen(filename);
    ext_len = ft_strlen(extension);
    if (file_len < ext_len)
        return 0;
    i = file_len - ext_len;
    return !ft_strncmp(&(filename[i]), extension, ext_len + 1);
}

void read_info(int fd, t_list *info)
{
    t_str *line;
    char ch;

    line = str_new();
    while(read(fd, &ch, 1) > 0 && info->count < 6)
    {
        if (line->count == 0 && ch == '\n')
            continue;
        if(line->count > 0 && ch == '\n')
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

int choose_flag(t_str *line, char flags)
{
    if (!ft_strncmp(line->content, "NO ", 3) &&
        !(flags & 1) && line->count > 3)
        return 1;
    if (!ft_strncmp(line->content, "SO ", 3) &&
        !(flags & 2) && line->count > 3)
        return 2;
    if (!ft_strncmp(line->content, "WE ", 3) &&
        !(flags & 4) && line->count > 3)
        return 4;
    if (!ft_strncmp(line->content, "EA ", 3) &&
        !(flags & 8) && line->count > 3)
        return 8;
    if (!ft_strncmp(line->content, "F ", 2) &&
        !(flags & 16) && line->count > 6)
        return 16;
    if (!ft_strncmp(line->content, "C ", 2) &&
        !(flags & 32) && line->count > 6)
        return 32;
    return 0;
}

int check_info(t_list *info)
{
    char flags;
    int i;
    t_str **lines;
    int result;

    if (info->count != 6)
        return 0;
    flags = 0;
    i = 0;
    lines = info->content;
    while(lines[i])
    {
        result = choose_flag(lines[i], flags);
        if (!result)
            return 0;
        flags += result;
        i++;
    }
    return flags;
}

int set_color(char *clr, char *str)
{
    int error;
    
    *clr = ft_atoi(str, &error);
    if (error)
        return false;
    return true;
}

bool set_colors(char *str, int *color)
{
    char *clr;
    char *strs;
    int len;

    clr = (char *)color;
    strs = ft_super_split(str, ",", "");
    len = ft_strslen(strs);
    if (len != 3)
        return false;
    if (!set_color(&(clr[2]), str[0]) == false)
        return false;
    if (!set_color(&(clr[1]), str[1]) == false)
        return false;
    if (!set_color(&(clr[0]), str[2]) == false)
        return false;
    return true;
}

bool set_img(char *str, t_data **img)
{
    *img = create_image(str);
    if (*img == NULL)
        return false;
    return true;
}

bool try_set_info(char **strs, t_info *info)
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

bool try_parse_info(t_list *str_info, t_info *info)
{
    int i;
    char **strs;
    t_str **lines;
    
    i = 0;
    lines = str_info->content;
    while(lines[i])
    {
        strs = ft_super_split(lines[i], " ", "");
        if (try_set_info(strs, info) == false)
            return false;
        i++;
    }
    return true;
}

t_game_map_status game_map(char *filename, t_info *info)
{
    int fd;
    t_list *str_info;
    
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
    return ok;
}
