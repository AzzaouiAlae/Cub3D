#include "cub3d.h"
#include "game_map/game_map.h"

void hanle_parsing_error(t_game_map_status status)
{
	if (status == ok)
		return;
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

void ft_init()
{
	g_mlx = mlx_init();
	mlx_get_screen_size(g_mlx, &g_width, &g_height);
	g_win = mlx_new_window(g_mlx, g_width, g_height, "Game");
	ft_bzero(&g_win_img, sizeof(t_data));
	g_win_img.img = mlx_new_image(g_mlx, g_width, g_height);
	g_win_img.addr = mlx_get_data_addr(g_win_img.img, &(g_win_img.bits_per_pixel), 
		&(g_win_img.line_length), &(g_win_img.endian));
	ft_bzero(&g_info, sizeof(t_info));
	g_map = list_new(sizeof(t_str *));
	ft_bzero(&g_player, sizeof(t_player));
}

void render_mini_map_border()
{
	int i;
	int j;

	i = 0;
	while (i < MIN_MAP_H)
	{
		j = 0;
		while (j < MIN_MAP_W)
		{
			if ((i >= 0 && i < MIN_MAP_BORDER_SIZE) || i >= MIN_MAP_H - MIN_MAP_BORDER_SIZE 
				|| (j >= 0 && j < MIN_MAP_BORDER_SIZE) || j >= MIN_MAP_W - MIN_MAP_BORDER_SIZE)
				my_mlx_put_pixel(&g_win_img, MIN_MAP_MARGIN_X + j,
					MIN_MAP_MARGIN_Y + i, 0xffffff);
			j++;
		}
		i++;
	}
}

void render_mini_map()
{

}

int render_game(void *pram)
{
	(void)pram;
	render_mini_map_border();
	render_mini_map();
	mlx_put_image_to_window(g_mlx, g_win, g_win_img.img, 0, 0);
	return 0;
}

int	main(int arg_c, char *arg_v[])
{
	if (arg_c != 2)
	{
		ft_putstr_fd(2, "Error\nInvalid args\n", 19);
		ft_exit(255);
	}
	ft_init();
	hanle_parsing_error(game_map(arg_v[1], &g_info));
	mlx_loop_hook(g_mlx, render_game, NULL);
	mlx_loop(g_mlx);
	ft_free_all();
}
