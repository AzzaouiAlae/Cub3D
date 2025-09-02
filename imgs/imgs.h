#ifndef IMGS_H
# define IMGS_H
# include "../cub3d.h"

# define FPS 30
# define E_FPS 10
# define N_FPS 10
# define S_FPS 10
# define W_FPS 10
# define O_FPS 25
# define C_FPS 25

t_data *get_east_img();
t_data *get_north_img();
t_data *get_south_img();
t_data *get_west_img();
t_data *get_open_door_img();
t_data *get_close_door_img();
t_data *get_wall_img(t_list *list, t_data *data, int *i, long *old_time);

#endif
