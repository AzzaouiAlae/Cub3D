SRC = main.c \
  		ft_func/ft_count_char.c ft_func/ft_strchr.c ft_func/ft_atoi.c	ft_func/ft_close.c	ft_func/ft_itoa.c	ft_func/ft_memcpy.c	ft_func/ft_open.c	ft_func/ft_putstr_fd.c	ft_func/ft_split.c	ft_func/ft_strdup.c	ft_func/ft_strjoin.c	ft_func/ft_strlcat.c	ft_func/ft_strlen.c	ft_func/ft_strncmp.c	ft_func/ft_strnstr.c	ft_func/ft_substr.c \
		map/map_hash_function.c map/map_add.c	map/map_clear.c	map/map_delete.c	map/map_get.c	map/map_new.c	map/prime_nums.c	map/resize.c \
		game_map/game_map.c \
		string/str_add.c	string/str_delete.c	string/str_insert.c	string/str_new.c	string/str_resize.c \
		garbage_collector/ft_calloc.c	garbage_collector/ft_save_mem.c	garbage_collector/mem_list.c	garbage_collector/ft_exit.c	garbage_collector/ft_free.c \
		list/list_add.c	list/list_contains.c	list/list_delete.c	list/list_insert.c	list/list_new.c	list/list_resize.c \
		map_game/map_game.c player/player.c raycasting/raycasting.c raycasting/utils.c raycasting/walls.c imgs/imgs.c hooks.c utils.c

OBJ =  main.o \
  		ft_func/ft_count_char.o ft_func/ft_strchr.o ft_func/ft_atoi.o	ft_func/ft_close.o	ft_func/ft_itoa.o	ft_func/ft_memcpy.o	ft_func/ft_open.o	ft_func/ft_putstr_fd.o	ft_func/ft_split.o	ft_func/ft_strdup.o	ft_func/ft_strjoin.o	ft_func/ft_strlcat.o	ft_func/ft_strlen.o	ft_func/ft_strncmp.o	ft_func/ft_strnstr.o	ft_func/ft_substr.o \
		map/map_hash_function.o map/map_add.o	map/map_clear.o	map/map_delete.o	map/map_get.o	map/map_new.o	map/prime_nums.o	map/resize.o \
		game_map/game_map.o \
		string/str_add.o	string/str_delete.o	string/str_insert.o	string/str_new.o	string/str_resize.o \
		garbage_collector/ft_calloc.o	garbage_collector/ft_save_mem.o	garbage_collector/mem_list.o	garbage_collector/ft_exit.o	garbage_collector/ft_free.o \
		list/list_add.o	list/list_contains.o	list/list_delete.o	list/list_insert.o	list/list_new.o	list/list_resize.o \
		map_game/map_game.o player/player.o raycasting/raycasting.o raycasting/utils.o raycasting/walls.o imgs/imgs.o hooks.o utils.o

CC = cc -Wall -Wextra -Werror
NAME=cub3D.out
f = -fsanitize=address
CFLAGS= -I/usr/include -I. -Imlx_linux -Imap_game -Iplayer -g3   # -O3
mlx = -Lmlx_linux -lmlx_Linux -L/usr/lib -L. -Imlx_linux -Imap_game -lXext -lX11 -lm -lz

all : mlx_vlc $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(mlx) vlc_mlx/libvlcmlx -o $(NAME)

mlx_vlc:
	@$(MAKE) -C vlc_mlx

clean :
	@$(MAKE) clean -C vlc_mlx
	rm -fr $(OBJ) $(vlc_OBJ)

fclean : clean
	@$(MAKE) fclean -C vlc_mlx
	rm -fr $(NAME)

re : fclean $(all)

.PHONY: all clean fclean re bonus
