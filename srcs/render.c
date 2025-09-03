/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:13:51 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/03 23:35:55 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Dibujar en pantalla lo que se ha cargado en el mapa (char **mapa), usando
	MiniLibX (mlx_put_image_to_window).

	- Recorrer el mapa fila a fila y columna a columna.
	- Según el carácter ('0', '1', 'C', 'E', 'P') dibujar:
		suelo (img_ground)
		pared (img_wall)
		item (img_item)
		salida (img_exit)
		jugador (img_player) → en la posición del jugador, no de P en el mapa.
	- Loop doble (for filas y columnas).
	- Para cada (i, j):
		Primero dibujar siempre el suelo (img_ground).
		Luego si el mapa tiene:
			'1' → dibujar pared (img_wall).
			'C' → dibujar item (img_item).
			'E' → dibujar salida (img_exit).
			'P' → no dibujar nada especial (porque ahora el jugador real se pinta aparte).
	- Dibujar jugador en g->pj.x y g->pj.y.
*/

#include "solong.h"

void	draw_sprite(t_game *game, t_img sprite, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, sprite.img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int		x;
	int		y;
	char	cell;

	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			cell = game->map.map[y][x];
			if (cell == MURO)
				draw_sprite(game, game->wall, x, y);
			else
			{
				draw_sprite(game, game->floor, x, y);
				if (cell == ITEM)
					draw_sprite(game, game->collectible, x, y);
				if (cell == EXIT)
				{
					if (game->map.collectible_count == 0)
						draw_sprite(game, game->exit_opened, x, y);
					else
						draw_sprite(game, game->exit_closed, x, y);
				}
			}
			x++;
		}
		y++;
	}
	draw_sprite(game, game->player, game->map.player_pos.x, game->map.player_pos.y);
	ft_printf("Movimientos: %d\n", game->moves);
}
