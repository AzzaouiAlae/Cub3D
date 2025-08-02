#ifndef CUB3D_H
#define CUB3D_H

#include "ft_func/ft_func.h"
#include "garbage_collector/garbage_collector.h"
#include "list/list.h"
#include "map/map.h"
#include "string/string.h"
#include <stdbool.h>
#include "global.h"
# include "/home/aazzaoui/Downloads/minilibx-linux/mlx.h"

#define MIN_MAP_H 150
#define MIN_MAP_W 200
#define MIN_MAP_MARGIN_X 100
#define MIN_MAP_MARGIN_Y 60
#define MIN_MAP_BORDER_SIZE 1
#define MIN_MAP_TIAL_SIZE 10




typedef struct s_line
{
    t_point start;
    t_point end;
} t_line;

typedef struct s_end_point
{
    t_point point;
    float distance;
    int color;
} s_end_point;

void	my_mlx_put_pixel(t_data *data, int x, int y, int color);
unsigned int	my_mlx_get_pixel(t_data *data, int x, int y);
t_data	*create_image(char *relative_path);

#endif