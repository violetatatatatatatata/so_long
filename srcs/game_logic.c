/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 game_logic.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 15:28:22 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:38:24 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

// Maneja el movimiento del jugador y la lógica del juego.
int	move_player(t_game *game, int new_x, int new_y)
{
	char	next_cell;

	next_cell = game->map.map[new_y][new_x];
	if (next_cell == MURO)
		return (0);
	if (next_cell == ITEM)
	{
		game->map.collectible_count--;
		game->map.map[new_y][new_x] = EMPTY;
	}
	if (next_cell == EXIT && game->map.collectible_count > 0)
		return (0);
	game->moves++;
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	if (next_cell == EXIT && game->map.collectible_count == 0)
	{
		ft_printf("¡Felicidades! Has terminado el juego en %d movimientos.\n",
			game->moves);
		exit_game(game);
	}
	return (1);
}

// Llama a la función de movimiento según la tecla presionada.
int	handle_key_press(int keycode, t_game *game)
{
	int	moved;

	moved = 0;
	if (keycode == 65307)
		exit_game(game);
	else if (keycode == 119 || keycode == 65362)
		moved = move_player(game, game->map.player_pos.x,
				game->map.player_pos.y - 1);
	else if (keycode == 115 || keycode == 65364)
		moved = move_player(game, game->map.player_pos.x,
				game->map.player_pos.y + 1);
	else if (keycode == 97 || keycode == 65361)
		moved = move_player(game, game->map.player_pos.x - 1,
				game->map.player_pos.y);
	else if (keycode == 100 || keycode == 65363)
		moved = move_player(game, game->map.player_pos.x + 1,
				game->map.player_pos.y);
	if (moved)
	{
		render_map(game);
		ft_printf("Movimientos: %d\n", game->moves);
	}
	return (0);
}

int	is_valid_format(char *str)
{
	int		len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 5)
		return (0);
	return (ft_strncmp(str + len - 4, ".ber", 4) == 0);
}
