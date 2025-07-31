#ifndef CUB3D_H
#define CUB3D_H

#include "ft_func/ft_func.h"
#include "garbage_collector/garbage_collector.h"
#include "list/list.h"
#include "map/map.h"
#include "string/string.h"
#include "global.h"
#include <stdbool.h>

typedef struct s_point
{
    float x;
    float y;
} t_point;

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

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_width;
	int				img_height;
}					t_data;

typedef struct s_info
{
    t_data *north;
    t_data *south;
    t_data *west;
    t_data *east;
    int floor_color;
    int ceil_color
} t_info;


void	my_mlx_put_pixel(t_data *data, int x, int y, int color);
unsigned int	my_mlx_get_pixel(t_data *data, int x, int y);
t_data	*create_image(char *relative_path);

#endif