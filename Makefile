# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avelandr <avelandr@student.42barcelon>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 12:30:28 by avelandr          #+#    #+#              #
#    Updated: 2025/09/04 12:46:20 by avelandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilador y sus flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Nombre del ejecutable
NAME = so_long

# Directorio de objetos
OBJ_DIR = objs

# Archivos fuente del proyecto
SRCS = srcs/main.c srcs/sprites.c srcs/checker.c srcs/map.c srcs/render.c srcs/bfs_run.c srcs/bfs.c srcs/bfs_utils.c srcs/game_logic.c srcs/utils.c

# Archivos objeto
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

# Rutas y nombres de las bibliotecas externas
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

# Flags para enlazar
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Inclusión de headers
INCLUDES = -I./srcs -I$(LIBFT_DIR)/Includes -I$(MLX_DIR)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: srcs/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

# Limpieza total: elimina objetos y el ejecutable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
