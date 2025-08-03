#ifndef CUB3D_H
#define CUB3D_H

#include "ft_func/ft_func.h"
#include "garbage_collector/garbage_collector.h"
#include "list/list.h"
#include "map/map.h"
#include "string/string.h"
#include <stdbool.h>
#include "global.h"
# include <mlx.h>
#include <unistd.h>
#include <math.h>

#define M_M_H 200
#define M_M_W 250
#define M_M_MARGIN_X 50
#define M_M_MARGIN_Y 40
#define M_M_BORDER_SIZE 1
#define M_M_TIAL_SIZE 20
#define PLAYER_SPEED 1
#define FRAME_PER_SEC 60
#define M_PI 3.14159265358979323846
#define ANGLE_SPEED 1

typedef enum e_side
{
	north,
	south,
	west,
	east,
} t_side;

typedef enum s_events
{
	on_keydown = 2,
	on_keyup = 3,
	on_mousedown = 4,
	on_mouseup = 5,
	on_mousemove = 6,
	on_expose = 12,
	on_destroy = 17
}					t_events;

typedef struct s_line
{
    t_point start;
    t_point end;
} t_line;

typedef struct s_end_point
{
    t_point point;
    t_side side;
    float distance;
} t_end_point;

void	my_mlx_put_pixel(t_data *data, int x, int y, int color);
unsigned int	my_mlx_get_pixel(t_data *data, int x, int y);
t_data	*create_image(char *relative_path);

#endif