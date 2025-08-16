/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:24:08 by avelandr          #+#    #+#             */
/*   Updated: 2025/08/16 17:29:08 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*	Algoritmo para Dibujar el Mapa
**	- Iterar sobre el mapa: Utiliza dos bucles anidados para recorrer cada
**	celda del mapa, desde la fila 0 hasta map_height - 1 y desde la columna
**	0 hasta map_width - 1.

**	Dibujar el fondo: En cada iteración, dibuja el sprite de la baldosa
**	(piso) t_game->floor.img en la posición actual. Esto crea el fondo
**	del nivel.

**	Dibujar el elemento: Usa una estructura de control (como if/else if)
**	para determinar qué elemento se encuentra en la celda actual
**	(map[y][x]) y dibuja su sprite correspondiente.

*	- Si es '1', dibuja la pared (t_game->wall.img).
*	- Si es 'C', dibuja el coleccionable (t_game->collectible.img).
*	- Si es 'E', dibuja la salida (t_game->exit.img).
*	- Si es 'P', dibuja al jugador (t_game->player.img).

**	Calcular la posición: La posición de dibujo en la ventana se calcula
**	multiplicando las coordenadas del mapa (x e y) por el tamaño de los
**	sprites (por ejemplo, 64 píxeles)
*/

// Función para dibujar una imagen en una posición específica
void	draw_image(t_game *game, t_img img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img.img, x * TILE_SIZE, y * TILE_SIZE);
}

// Función para dibujar el mapa, fondo y elementos
void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			// Dibuja el fondo de baldosa en cada celda
			draw_image(game, game->floor, x, y);
			// Dibuja los elementos no móviles
			if (game->map[y][x] == '1')
				draw_image(game, game->wall, x, y);
			else if (game->map[y][x] == 'C')
				draw_image(game, game->collectible, x, y);
			else if (game->map[y][x] == 'E')
				draw_image(game, game->exit, x, y);
			// Dibuja el jugador en su posición actual
			else if (game->map[y][x] == 'P')
				draw_image(game, game->player, x, y);
			x++;
		}
		y++;
	}
}

// Actualiza la posición del jugador en la estructura del juego
void	update_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
