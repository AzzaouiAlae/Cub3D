SRC = main.c \
		game_parse/game_parse.c game_parse/parse_info.c game_parse/parse_list_info.c game_parse/parse_map.c game_parse/read_info.c\
		string/str_add.c	string/str_delete.c	string/str_insert.c	string/str_new.c	string/str_resize.c \
		garbage_collector/ft_calloc.c	garbage_collector/ft_save_mem.c	garbage_collector/mem_list.c	garbage_collector/ft_exit.c	garbage_collector/ft_free.c \
		list/list_add.c	list/list_contains.c	list/list_delete.c	list/list_insert.c	list/list_new.c	list/list_resize.c \
		map_game/map_game.c player/player.c raycasting/raycasting.c imgs/imgs.c imgs/door_imgs.c raycasting/draw_floor_ceil.c render_game.c\
		player/player_calc.c	player/player_teleportation_move.c raycasting/utils.c raycasting/walls.c hooks.c utils.c raycasting/door_info.c \
		ft_func/ft_count_char.c ft_func/ft_strchr.c ft_func/ft_atoi.c ft_func/ft_split.c ft_func/ft_substr.c \
		ft_func/ft_memcpy.c	ft_func/ft_open.c	ft_func/ft_putstr_fd.c	ft_func/ft_strdup.c	ft_func/ft_strlen.c	ft_func/ft_strncmp.c \

OBJ =  main.o \
		game_parse/game_parse.o game_parse/parse_info.o game_parse/parse_list_info.o game_parse/parse_map.o game_parse/read_info.o \
		string/str_add.o	string/str_delete.o	string/str_insert.o	string/str_new.o	string/str_resize.o \
		garbage_collector/ft_calloc.o	garbage_collector/ft_save_mem.o	garbage_collector/mem_list.o	garbage_collector/ft_exit.o	garbage_collector/ft_free.o \
		list/list_add.o	list/list_contains.o	list/list_delete.o	list/list_insert.o	list/list_new.o	list/list_resize.o \
		map_game/map_game.o player/player.o raycasting/raycasting.o imgs/imgs.o imgs/door_imgs.o raycasting/draw_floor_ceil.o render_game.o\
		player/player_calc.o	player/player_teleportation_move.o raycasting/utils.o raycasting/walls.o hooks.o utils.o raycasting/door_info.o \
		ft_func/ft_count_char.o ft_func/ft_strchr.o ft_func/ft_atoi.o ft_func/ft_split.o ft_func/ft_substr.o \
		ft_func/ft_memcpy.o	ft_func/ft_open.o	ft_func/ft_putstr_fd.o	ft_func/ft_strdup.o	ft_func/ft_strlen.o	ft_func/ft_strncmp.o \

CC = cc
NAME=cub3D.out
f = -fsanitize=address
#-Werror
CFLAGS= -Wall -Wextra -O3
mlx = -lmlx_Linux -lXext -lX11 -lm

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
