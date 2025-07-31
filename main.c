#include "cub3d.h"

void	*g_mlx;
void	*g_win;
t_list	*g_map;
t_info	*g_info;
t_data  *g_win_img;

int	main(int arg_c, char *arg_v[])
{
	t_str	*str;

	(void)arg_c;
	(void)arg_v;
	str = str_new();
	str_add(str, "hello\n");
	write(1, str->content, str->count);
	ft_free_all();
}
