#include "game_parse.h"

void add_one_to_str(t_str *str)
{
	str->content[str->count - 5]++;
	if (str->content[str->count - 5] > '9')
	{
		str->content[str->count - 5] = '0';
		str->content[str->count - 6]++;
	}
}

bool	set_img_list(char *path, t_list **imgs)
{
	t_str *str;
	t_data *img;

	str = str_new();
	*imgs = list_new(sizeof(t_data *));
	str_add(str, path);
	str_add(str, "/img_00.xpm");
	while (true)
	{
		add_one_to_str(str);
		if (access(str->content, R_OK))
			break;
		img = create_image(str->content);
		if (img == NULL)
			return false;
		list_add(*imgs, (long)img);
		if (str->content[str->count - 6] == '9'
			&& str->content[str->count - 5] == '9')
			break;
	}
	return ((*imgs)->count > 0);
}

bool parce_img_list(char **strs, t_info *info)
{
	if (!ft_strncmp(strs[0], "NO", 3))
		return set_img_list(strs[1], &(info->list_north));
	else if (!ft_strncmp(strs[0], "SO", 3))
		return set_img_list(strs[1], &(info->list_south));
	else if (!ft_strncmp(strs[0], "WE", 3))
		return set_img_list(strs[1], &(info->list_west));
	else if (!ft_strncmp(strs[0], "EA", 3))
		return set_img_list(strs[1], &(info->list_east));
	else if (!ft_strncmp(strs[0], "DO", 3))
		return set_img_list(strs[1], &(info->list_open_door));
	else if (!ft_strncmp(strs[0], "DC", 3))
		return set_img_list(strs[1], &(info->list_close_door));
	if (!ft_strncmp(strs[0], "F", 2))
		return set_colors(strs[1], &(info->floor_color));
	if (!ft_strncmp(strs[0], "C", 2))
		return set_colors(strs[1], &(info->ceil_color));
	return false;
}
