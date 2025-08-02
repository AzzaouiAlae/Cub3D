#ifndef GLOBAL_H
# define GLOBAL_H
#include <sys/time.h>

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;
}				t_data;

typedef struct s_info
{
	t_data		*north;
	t_data		*south;
	t_data		*west;
	t_data		*east;
	int			floor_color;
	int			ceil_color;
}				t_info;

typedef struct s_point
{
    float x;
    float y;
} t_point;

typedef struct s_player
{
	t_point pos;
	t_point map_pos;
	float angle;
} t_player;

typedef struct  s_pressed_keys
{
	char w;
	char s;
	char a;
	char d;
} t_keys;


extern t_list	*g_map;
extern void		*g_mlx;
extern void		*g_win;
extern t_info	g_info;
extern t_data	g_win_img;
extern int		g_width;
extern int		g_height;
extern t_player g_player;
extern t_keys g_keys;
extern struct timeval g_start_time;

#endif