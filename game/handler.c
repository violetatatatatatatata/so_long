/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:48:50 by avelandr          #+#    #+#             */
/*   Updated: 2025/08/16 17:55:18 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

// Función para liberar la memoria y cerrar el juego
int	close_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// mlx_destroy_image(game->mlx, game->wall.img);
	while (i < game->map_height)
		free(game->map[i++]);
	free(game->map);
	exit(0);
}

// Función para verificar si todos los coleccionables han sido recolectados
static int	all_collectible_collected(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

// Función para mover al jugador y actualizar el estado del juego
static void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == '1')
		return ; // La nueva posición es un muro, no hace nada
	game->map[game->player_y][game->player_x] = '0'; // La posición antigua se convierte en piso
	if (game->map[new_y][new_x] == 'C')
	{
		game->collect_count++;
		game->map[new_y][new_x] = '0'; // El coleccionable se convierte en piso
		if (all_collectible_collected(game))
			printf("All collectibles collected! The exit is now open.\n"); // O cambia el sprite de la salida
	}
	else if (game->map[new_y][new_x] == 'E')
	{
		if (all_collectible_collected(game))
			close_game(game); // Si todos los coleccionables están recolectados, el jugador sale
	}
	game->map[new_y][new_x] = 'P'; // Mueve el jugador a la nueva posición
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	printf("Moves: %d\n", game->moves);
	draw_map(game); // Redibuja el mapa después del movimiento
}

// Manejador de eventos del teclado
int	key_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == KEY_S)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == KEY_A)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == KEY_D)
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}

// En el main, asegúrate de que el hook de cierre esté configurado
// mlx_hook(game.win, EVENT_DESTROY_NOTIFY, 0, close_game, &game);
// Ten en cuenta que el segundo parámetro de mlx_hook, `event_mask` para `EVENT_DESTROY_NOTIFY` es 1L << 17

