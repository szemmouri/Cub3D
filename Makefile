NAME     = cub3D

CC       = cc
CFLAGS   = -Wall -Wextra -Werror

GNLDIR = includes/gnl
LIBFTDIR = includes/libft


MLXDIR = includes/mlx
LMLX = $(MLXDIR)/libmlx.a -framework OpenGL -framework AppKit
LIBFT = $(LIBFTDIR)/libft.a


SRCS = \
	main.c \
	parcing/check_file.c \
	parcing/check_map_closed.c \
	parcing/check_map.c \
	parcing/check_textures.c \
	parcing/create_map.c \
	parcing/fill_color_textures.c \
	parcing/get_file_data.c \
	parcing/init_game.c \
	parcing/init_player_dir.c \
	parcing/parcing_utils.c \
	parcing/parse_data.c \
	free_game.c \
	render/render_init.c \
	render/render_drawing.c \
	render/render_textures.c \
	render/render_utils.c \
	render/render_raycasting.c \
	render/render_player.c \
	render/render_main.c \
	render/render_drawing_map.c \
	render/render_utils1.c \
	$(GNLDIR)/get_next_line.c $(GNLDIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MAKE) -C $(MLXDIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LMLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
