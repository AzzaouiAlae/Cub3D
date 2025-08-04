#ifndef MIN_MAP_C
#define MIN_MAP_C
#include "../cub3d.h"

void put_pixel_min_map(float x, float y, int color);
void	clear_img(t_line area);
void	render_mini_map(void);
bool is_in_mini_map(int x, int y);
void init_mini_map_border(t_line	*border);

#endif