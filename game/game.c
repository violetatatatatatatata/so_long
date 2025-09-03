/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:15:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/08/16 17:24:00 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

// Función para manejar el evento de cierre de ventana (botón de la X)
int	close_handler(t_game *game)
{
	// Aquí debes liberar toda la memoria del juego de manera segura
	// Por ejemplo:
	// mlx_destroy_image(game->mlx, game->wall.img);
	// mlx_destroy_window(game->mlx, game->win);
	// free_map(game->map, game->map_height);
	// etc.
	exit(0);
}

// Función para manejar las pulsaciones de teclas
int	key_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_handler(game);
	// Manejar otros movimientos (W, A, S, D)
	if (keycode == KEY_W)
		move_up(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_S)
		move_down(game);
	else if (keycode == KEY_D)
		move_right(game);
	return (0);
}

// Función principal del bucle de juego
int	loop_hook(t_game *game)
{
	// Lógica de actualización del juego, como animaciones, movimientos de enemigos, etc.
	// Por ahora, solo puedes volver a dibujar el mapa si es necesario
	return (0);
}

/* Función para inicializar el juego
**	- Inicializa minilibX, crea la ventana y carga los sprites
*/
int	init_game(t_game *game, char **map, int map_width, int map_height)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, map_width * 64, map_height * 64, "so_long");
	if (!game->win)
	{
		free(game->mlx);
		return (1);
	}
	game->map = map;
	game->map_width = map_width;
	game->map_height = map_height;
	game->moves = 0;
	game->collect_count = 0;
	// Carga los sprites
	// game->wall.img = mlx_xpm_file_to_image(game->mlx, "./sprites/wall.xpm", &game->wall.width, &game->wall.height);
	// ... Cargar todos los sprites necesarios
	return (0);
}

// Llama a las funciones de inicialización y configura los hooks (funciones de devolución de llamada que se ejecutan cuando ocurre un evento en específico)
int	setup_hooks(t_game *game)
{
	mlx_hook(game->win, EVENT_KEY_PRESS, 1L << 0, key_handler, game);
	mlx_hook(game->win, EVENT_DESTROY_NOTIFY, 1L << 5, close_handler, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	return (0);
}

// Función principal
int	main(int argc, char **argv)
{
	t_game	game;
	char	**map;
	int		width;
	int		height;

	if (argc != 2)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	map = parse_map(argv[1], &width, &height);
	if (!map)
	{
		printf("Error: Map validation failed.\n");
		return (1);
	}
	if (init_game(&game, map, width, height) != 0)
	{
		printf("Error: Game initialization failed.\n");
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
