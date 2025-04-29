/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:47:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/04/26 13:11:02 by avelandr         ###   ########.fr       */
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
	int	pos_x;
	int	pos_y;
} t_mapa

typedef struct
{
	int	movimientos;
} t_personaje;

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

// funciones

#endif
