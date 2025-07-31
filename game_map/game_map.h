#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "../cub3d.h"

typedef enum e_game_map_status
{
    ok,
    err_file_extension,
    err_open_file,
    err_invalid_info,
    err_invalid_map,
    err_invalid_player_pos,
} t_game_map_status;

t_game_map_status game_map(char *filename, t_info info);
int file_extension(char *filename, char *extension);
void read_info(int fd, t_list *str_info);
int check_info(t_list *str_info);

#endif