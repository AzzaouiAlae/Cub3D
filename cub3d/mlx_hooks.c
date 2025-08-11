#include "cub3d.h"
#include "player/player.h"
#include "min_map/min_map.h"

void clear_win_img()
{
	int x;
	int y;

	y = 0;
	while (y < g_height)
	{
		x = 0;
		while(x < g_width)
		{
			my_mlx_put_pixel(&g_win_img, x, y, 0x0);
			x++;
		}
		y++;
	}
}

int	render_game(void *pram)
{
	(void)pram;
	clear_win_img();
	render_mini_map();
	player_render();
	mlx_put_image_to_window(g_mlx, g_win, g_win_img.img, 0, 0);
	mlx_put_image_to_window(g_mlx, g_win, g_min_map_img.img, M_M_MARGIN_X, M_M_MARGIN_Y);
	limit_frame_speed();
	count_frame_per_sec();
	return (0);
}

int	close_window(void *param)
{
	(void)param;
	ft_exit(0);
	return (0);
}

int	keydown_hook(int keycode, void *var)
{
	char	ch;

	ch = (char)keycode;
	(void)var;
	if (keycode == 65307)
		ft_exit(0);
	else if (!g_keys.w && ch == 'w')
		g_keys.w = 1;
	else if (!g_keys.a && ch == 'a')
		g_keys.a = 1;
	else if (!g_keys.d && ch == 'd')
		g_keys.d = 1;
	else if (!g_keys.s && ch == 's')
		g_keys.s = 1;
	else if (!g_keys.right && ch == 83)
		g_keys.right = 1;
	else if (!g_keys.left && ch == 81)
		g_keys.left = 1;
	return (0);
}

int	keyup_hook(int keycode, void *var)
{
	char	ch;

	ch = (char)keycode;
	(void)var;
	if (ch == 'w')
		g_keys.w = 0;
	else if (ch == 'a')
		g_keys.a = 0;
	else if (ch == 'd')
		g_keys.d = 0;
	else if (ch == 's')
		g_keys.s = 0;
	else if (ch == 83)
		g_keys.right = 0;
	else if (ch == 81)
		g_keys.left = 0;
	return (0);
}
