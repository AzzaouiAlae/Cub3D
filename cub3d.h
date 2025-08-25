#ifndef CUB3D_H
# define CUB3D_H

# include "ft_func/ft_func.h"
# include "garbage_collector/garbage_collector.h"
# include "global.h"
# include "list/list.h"
# include "map/map.h"
# include "string/string.h"
# include "player/player.h"
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <unistd.h>


# define MAP_HEIGHT 200.0
# define MAP_W 300.0
# define MAP_MARGIN_X 50.0
# define MAP_MARGIN_Y 40.0
# define MAP_BORDER_SIZE 1.0
# define TILESIZE 40
# define PLAYER_SPEED 120.0
# define M_PI 3.14159265358979323846
# define ANGLE_SPEED 160.0
# define FOV 60.0
# define SAFETY 10
# define DPI 0.08

typedef enum e_side
{
	north,
	south,
	west,
	east,
	close_door,
	open_door,
}					t_side;

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
	t_point			start;
	t_point			end;
}					t_line;

typedef struct s_end_point
{
	t_point			side_dist;
	t_point			delta_dist;
	t_point			end;
	t_side			side;
	double			distance;
}					t_end_point;

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}					t_color;

void				my_mlx_put_pixel(t_data *data, int x, int y, int color);
unsigned int		my_mlx_get_pixel(t_data *data, int x, int y);
t_data				*create_image(char *relative_path);
double ph_distance(t_point p1, t_point p2);
int					keyup_hook(int keycode, void *var);
int					keydown_hook(int keycode, void *var);
int					close_window(void *param);
int					render_game(void *pram);
size_t				get_curr_time(void);
void	normalize_angle(double *angle);
int mouse_hook(void *param);

#endif
