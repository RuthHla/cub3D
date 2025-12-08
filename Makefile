NAME = cub3d

SRCFILES =	get_next_line/get_next_line_utils.c \
			get_next_line/get_next_line.c \
			map_grid.c \
			camera.c \
			display.c \
			movement.c \
			check_move.c \
			draw_line.c \
			utils.c \
			horizontal_rays.c \
			vertical_rays.c \
			raycaster.c \
			render.c \
			loop.c \
			exit.c \
			main.c

OBJFILES = $(SRCFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g3

MLXFLAGS = -Iminilibx -Lminilibx -lmlx -lXext -lX11 -lm

MLXPATH = minilibx

MLXLIB = $(MLXPATH)/libmlx_Linux.a

CC = cc

RM = rm -f

$(NAME): $(OBJFILES)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJFILES) $(MLXLIB) $(MLXFLAGS)

all: $(NAME)

clean:
			$(RM) $(OBJFILES)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
