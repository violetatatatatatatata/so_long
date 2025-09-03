/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:29:06 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/03 23:32:59 by avelandr         ###   ########.fr       */
/*                                                                            */
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
void	open_map(t_game *game, const char *map_path);
int		check_rectangle(t_game *game);
int  check_walls(t_game *game);
int  count_elements(t_game *game);
int		is_valid_map(t_game *game);

// game_logic.c
void	move_player(t_game *game, int new_x, int new_y);
int		handle_key_press(int keycode, t_game *game);

// sprite_init.c
void	init_sprites(t_game *game);
void    load_sprite(t_game *game, t_img *sprite, char *path);

// render.c
void	render_map(t_game *game);
void    draw_sprite(t_game *game, t_img sprite, int x, int y);

// bfs.c
int		is_path_valid(t_game *game);
int is_valid_bfs_position(t_map *map, int x, int y, int **visited);
void    free_visited_array(int **visited, int height);
char **copy_map(t_map *map);
int bfs_path_checker(t_game *game);

// utils.c
char	**append_str_to_array(char **array, char *str);
void	exit_game(t_game *game);
int		on_destroy(t_game *game);
void    ft_free_array(char **array);

#endif
