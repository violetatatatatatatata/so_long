/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:13:51 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/04 10:56:35 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

// Dibuja el sprite correcto para una sola celda
void	render_tile(t_game *game, int x, int y)
{
	char	cell;

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
}

// Renderiza todo el mapa, llamando a render_tile para cada celda.
void	render_map(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
	draw_sprite(game, game->player, game->map.player_pos.x,
		game->map.player_pos.y);
}

void	load_map_lines(t_game *game, int fd)
{
	char	*line;
	int		len;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map.map = append_str_to_array(game->map.map, line);
		game->map.height++;
		free(line);
	}
}
