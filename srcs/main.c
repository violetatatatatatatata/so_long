/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:22:30 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/03 21:48:42 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error: Se necesita 1 argumento: la ruta del mapa.\n");
		return (EXIT_FAILURE);
	}
	ft_bzero(&game, sizeof(t_game));
	game.moves = 0;
	open_map(&game, argv[1]);
	if (!is_valid_map(&game))
	{
		ft_printf("Error: Mapa inválido.\n");
		exit_game(&game);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("Error: No se pudo inicializar mlx.\n");
		exit_game(&game);
	}
	game.win = mlx_new_window(game.mlx, game.map.width * TILE_SIZE,
			game.map.height * TILE_SIZE, "so_long");
	if (!game.win)
	{
		ft_printf("Error: No se pudo crear la ventana.\n");
		exit_game(&game);
	}
	init_sprites(&game);
	render_map(&game);
	mlx_key_hook(game.win, handle_key_press, &game);
	mlx_hook(game.win, 17, 0, on_destroy, &game);
	mlx_loop(game.mlx);
	return (0);
}
