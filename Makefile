NAME = minimap
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c parsing/parse.c init/init.c
# SRC = minimap.c
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

MLX_DIR = ./minilibx_macos
LIBFT_DIR = ./libft

# linux = 	MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lm -lXext -lX11
# macos =	MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

#MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lm -lXext -lX11
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
LIBFT_FLAGS = -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft


all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
