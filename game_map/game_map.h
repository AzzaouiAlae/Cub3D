#ifndef GAME_MAP_H
# define GAME_MAP_H
# include "../cub3d.h"

typedef enum e_game_map_status
{
	ok,
	err_file_extension,
	err_open_file,
	err_invalid_info,
	err_invalid_map,
}					t_game_map_status;

t_game_map_status	game_map(char *filename, t_info *info);
int					file_extension(char *filename, char *extension);
void				read_info(int fd, t_list *info);
int					check_info(t_list *str_info);
bool				try_parse_info(t_list *str_info, t_info *info);
bool				read_map(t_list *map, int fd);
bool				check_map(t_list *map, t_player *player);

#endif
