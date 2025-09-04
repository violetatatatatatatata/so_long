/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 map.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/04/26 11:06:19 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 00:45:09 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

void	open_map(t_game *game, const char *map_path)
{
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: No se pudo abrir el archivo de mapa.\n");
		exit_game(game);
	}
	game->map.height = 0;
	game->map.map = NULL;
	load_map_lines(game, fd);
	close(fd);
	if (game->map.height == 0)
	{
		ft_printf("Error: Mapa vacío.\n");
		exit_game(game);
	}
	game->map.width = ft_strlen(game->map.map[0]);
}

int	handle_cell(t_game *game, int x, int y)
{
	if (game->map.map[y][x] == INIT_POINT)
	{
		game->map.player_pos.x = x;
		game->map.player_pos.y = y;
		game->map.player_count++;
	}
	else if (game->map.map[y][x] == EXIT)
	{
		game->map.exit_pos.x = x;
		game->map.exit_pos.y = y;
		game->map.exit_count++;
	}
	else if (game->map.map[y][x] == ITEM)
		game->map.collectible_count++;
	else if (game->map.map[y][x] != MURO && game->map.map[y][x] != EMPTY)
		return (0);
	return (1);
}

// Itera sobre el mapa y llama a la función para manejar cada celda.
void	map_loop_count(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (!handle_cell(game, x, y))
				return ;
		}
	}
}
