/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:47:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/04/29 17:13:22 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include "mlx.h"

// Para los movimientos
#define ARRIBA 'W'
#define ABAJO 'S'
#define IZQ 'A'
#define DER 'D'
#define ESC 65307

// Para el mapa
#define EMPTY 0
#define MURO 1
#define ITEM 'C'
#define EXIT 'E'
#define INIT_POINT 'P'

typedef struct
{
	char	**mapa;	// mapa guardado como un array de strings
	int	filas;
	int	column;
	int	items;
} t_mapa;

typedef struct s_pos
{
    int x;
    int y;
} t_pos;

typedef struct s_game
{
        void    	*img_wall;	    // Sprites (las imágenes 2D del entorno gráfico)
        void    	*img_ground;
        void    	*img_item;
        void    	*img_exit;
        void    	*img_player;
	void		*mlx;         // puntero al sistema MiniLibX
	void		*win;         // puntero a la ventana abierta
	t_mapa		mapa;         // el mapa con todo su contenido
	t_personaje	pj;           // el jugador
} t_game;

// map.c
void    abrir_mapa(t_mapa *m);
char    **append_line(char **mapa, char *line, int filas);
int		is_valid_map(t_mapa *m);
int		check_muros(t_mapa *m);
int		check_PEC(t_mapa *m);

// bfs.c
int		is_valid_position(t_mapa *m, int x, int y);
void	 free_visited(int **visited, int filas);
int		**init_visited(int filas, int column);
int		bfs_algorithm(t_mapa *m, t_pos *queue, int **visited);
int		shortest_path(t_mapa *m);

// input.c
void set_moves(t_pos moves[4], t_pos c);
int handle_key(int keycode, t_game *g);
int set_next_move(int keycode, t_pos moves[4], t_pos *next, t_game *g);

#endif
