# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avelandr <avelandr@student.42barcelon>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 12:30:28 by avelandr          #+#    #+#              #
#    Updated: 2025/09/03 21:53:08 by avelandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilador y sus flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Nombre del ejecutable
NAME = so_long

# Archivos fuente del proyecto
SRCS = srcs/main.c srcs/map.c srcs/render.c srcs/sprite_init.c srcs/bfs.c srcs/game_logic.c srcs/utils.c

# Archivos objeto
OBJS = $(SRCS:.c=.o)

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

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)  # ← Agregar $(MLX_LIB) aquí
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

# Limpieza total: elimina objetos y el ejecutable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompilar todo (limpia y luego compila)
re: fclean all

# Indicamos a make que estos son "phony targets" y no archivos reales
.PHONY: all clean fclean re $(LIBFT_LIB)
