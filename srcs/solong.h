/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:13:48 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/04 02:30:52 by avelandr         ###   ########.fr       */
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

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		collectible_count;
	int		player_count;
	int		exit_count;
	t_pos	player_pos;
	t_pos	exit_pos;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

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

// ==================== main.c ====================
int		main(int argc, char **argv);
void	print_errores(t_game *game);

// ==================== map.c ====================
void	open_map(t_game *game, const char *map_path);
void	load_map_lines(t_game *game, int fd);
int		handle_cell(t_game *game, int x, int y);
void	map_loop_count(t_game *game);

// ==================== checker.c ====================
int		check_rectangle(t_game *game);
int		check_walls(t_game *game);
int		is_valid_map(t_game *game);

// ==================== bfs.c ====================
int     count_elements(t_game *game);
int		bfs_path_checker(t_game *game);

// ==================== bfs_utils.c ====================
int		process_cell(t_game *game, int y, int x);

// ==================== game_logic.c ====================
void	move_player(t_game *game, int new_x, int new_y);
int		handle_key_press(int keycode, t_game *game);

// ==================== render.c ====================
void	draw_sprite(t_game *game, t_img sprite, int x, int y);
void	render_tile(t_game *game, int x, int y);
void	render_map(t_game *game);

// ==================== sprite_init.c ====================
void	load_sprite(t_game *game, t_img *sprite, char *path);
void	init_sprites(t_game *game);

// ==================== utils.c ====================
void	ft_free_array(char **array);
void	exit_game(t_game *game);
int		on_destroy(t_game *game);
char	**append_str_to_array(char **array, char *str);

#endif
