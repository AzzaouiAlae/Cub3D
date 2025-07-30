#include "cub3d.h"

int main(int arg_c, char *arg_v[])
{
    (void)arg_c;
    (void)arg_v;
    t_str *str = str_new();

    str_add(str, "hello\n");

    write(1, str->content, str->count);
    ft_free_all();
}