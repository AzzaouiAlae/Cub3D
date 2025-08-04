#include "cub3d.h"
#include "game_map/game_map.h"

void	hanle_parsing_error(t_game_map_status status)
{
	if (status == ok)
		return ;
	if (status == err_file_extension)
		ft_putstr_fd(2, "Error\nInvalid extension\n", 24);
	if (status == err_open_file)
		ft_putstr_fd(2, "Error\nOpen file\n", 16);
	if (status == err_invalid_info)
		ft_putstr_fd(2, "Error\nInvalid info\n", 19);
	if (status == err_invalid_map)
		ft_putstr_fd(2, "Error\nInvalid map\n", 18);
	ft_exit(255);
}

void	ft_init(void)
{
	g_mlx = mlx_init();
	mlx_get_screen_size(g_mlx, &g_width, &g_height);
	g_win = mlx_new_window(g_mlx, g_width, g_height, "Game");
	ft_bzero(&g_win_img, sizeof(t_data));
	g_win_img.img = mlx_new_image(g_mlx, g_width, g_height);
	g_win_img.addr = mlx_get_data_addr(g_win_img.img,
			&(g_win_img.bits_per_pixel), &(g_win_img.line_length),
			&(g_win_img.endian));
	ft_bzero(&g_info, sizeof(t_info));
	g_map = list_new(sizeof(t_str *));
	ft_bzero(&g_player, sizeof(t_player));
	ft_bzero(&g_keys, sizeof(t_keys));
	gettimeofday(&g_start_time, NULL);
}

int	main(int arg_c, char *arg_v[])
{
	if (arg_c != 2)
	{
		ft_putstr_fd(2, "Error\nInvalid args\n", 19);
		exit(255);
	}
	ft_init();
	hanle_parsing_error(game_map(arg_v[1], &g_info));
	mlx_hook(g_win, on_destroy, 0, close_window, NULL);
	mlx_hook(g_win, on_keydown, 1L << 0, keydown_hook, NULL);
	mlx_hook(g_win, on_keyup, 1L<<1, keyup_hook, NULL);
	mlx_loop_hook(g_mlx, render_game, NULL);
	mlx_loop(g_mlx);
	ft_free_all();
}
