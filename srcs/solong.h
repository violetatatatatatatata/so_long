/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 solong.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:29:06 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 09:19:05 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/Includes/libft.h"
# include "../minilibx-linux/mlx.h"

# define TILE_SIZE 64
# define EMPTY '0'
# define MURO '1'
# define ITEM 'C'
# define EXIT 'E'
# define INIT_POINT 'P'

// Estructura para almacenar las coordenadas
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

// Estructura para aplicar el bfs
typedef struct s_bfs
{
	t_pos	*queue;
	int		**visited;
	int		front;
	int		back;
	int		items_to_collect;
	int		found_exit;
}	t_bfs;

// Estructura para almacenar el mapa
typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		collectible_count;
	t_pos	player_pos;
	t_pos	exit_pos;
}	t_map;

// Estructura para almacenar las imágenes
typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

// Estructura principal del juego
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	floor;
	t_img	wall;
	t_img	collectible;
	t_img	player;
	t_img	exit_closed;
	t_img	exit_opened;
	int		moves;
}	t_game;

// map.c
void	process_line(t_game *game, char *line);
void	open_map(t_game *game, char *map_path);
void	process_cell(t_game *game, int x, int y, int *counts);
int		validate_counts(int p_count, int e_count, int c_count);
int		count_elements(t_game *game);

// checker.c
int		check_rectangle(t_game *game);
int		check_horizontal_walls(t_game *game);
int		check_vertical_walls(t_game *game);
int		check_walls(t_game *game);
int		is_valid_map(t_game *game);

// game_logic.c
int		move_player(t_game *game, int new_x, int new_y);
int		handle_key_press(int keycode, t_game *game);
int		is_valid_format(char *str);

// render.c
void	render_map(t_game *game);
void	load_map_lines(t_game *game, int fd);
void	render_tile(t_game *game, int x, int y);

// sprites.c
void	load_sprite(t_game *game, t_img *sprite, char *path);
void	init_sprites(t_game *game);
void	draw_sprite(t_game *game, t_img sprite, int x, int y);

// bfs.c
char	**copy_map_loop(t_map *map, char **copy);
char	**copy_map(t_map *map);
void	process_current_cell(t_bfs *data, char **map_copy, t_pos current);
void	process_queue(t_game *game, t_bfs *data, char **map_copy);
void	enqueue_neighbors(t_game *game, t_bfs *data, t_pos current);

// bfs_utils.c
int		is_valid_bfs_position(t_map *map, int x, int y, int **visited);
int		bfs_path_checker(t_game *game);
void	free_visited_array(int **visited, int height);
void	free_bfs_data(t_bfs *data, t_game *game);
void	free_and_return(t_bfs *data, t_game *game, char **map_copy);

// bfs_run.c
int		init_visited_loop(t_game *game, int **visited);
int		init_bfs_data(t_game *game, t_bfs *data, char **map_copy);
int		**init_visited(t_game *game);
int		init_queue(t_game *game, t_bfs *data);

// utils.c
char	**append_str_aux(char **array, char *str);
char	**append_str_to_array(char **array, char *str);
void	exit_game(t_game *game);
int		on_destroy(t_game *game);
void	ft_free_array(char **array);

// main.c
void	print_errores(t_game *game);

#endif
