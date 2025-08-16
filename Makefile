# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avelandr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 12:30:28 by avelandr          #+#    #+#              #
#    Updated: 2025/08/16 18:07:56 by avelandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilador y sus flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Nombre del ejecutable
NAME = so_long

# Directorios de la librer\ufffd\ufffda y las im\ufffdgenes
MLX_DIR = mlx_linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lX11 -lXext

# Lista de archivos fuente obligatorios
SRCS = src/so_long.c \
	   src/map_parser.c \
	   src/map_validator.c \
	   src/game_hooks.c \
	   src/drawing_functions.c \
	   src/utils.c

# Archivos objeto
OBJS = $(SRCS:src/%.c=objs/%.o)

# Encabezados
HEADERS = includes/so_long.h

# Regla para el objetivo principal (obligatorio)
all: $(NAME)

# Regla para el ejecutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

# Regla para compilar los archivos fuente
objs/%.o: src/%.c $(HEADERS)
	@mkdir -p objs
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

# Limpiar los archivos objeto
clean:
	rm -rf objs

# Limpiar los archivos objeto y el ejecutable
fclean: clean
	rm -f $(NAME)

# Reconstruir el proyecto
re: fclean all

.PHONY: all clean fclean re
