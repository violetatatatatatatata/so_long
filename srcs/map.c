/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:06:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/04 12:07:05 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	process_line(t_game *game, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	game->map.map = append_str_to_array(game->map.map, line);
	game->map.height++;
	free(line);
}

void	open_map(t_game *game, char *map_path)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0 || !is_valid_format(map_path))
	{
		ft_printf("Error: No se pudo abrir el archivo de mapa.\n");
		exit_game(game);
	}
	game->map.height = 0;
	game->map.map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(game, line);
	}
	close(fd);
	if (game->map.height == 0)
	{
		ft_printf("Error: Mapa vacío.\n");
		exit_game(game);
	}
	game->map.width = ft_strlen(game->map.map[0]);
}

void	process_cell(t_game *game, int x, int y, int *counts)
{
	if (game->map.map[y][x] == INIT_POINT)
	{
		counts[0]++;
		game->map.player_pos.x = x;
		game->map.player_pos.y = y;
	}
	else if (game->map.map[y][x] == EXIT)
	{
		counts[1]++;
		game->map.exit_pos.x = x;
		game->map.exit_pos.y = y;
	}
	else if (game->map.map[y][x] == ITEM)
		game->map.collectible_count++;
	else if (game->map.map[y][x] != MURO && game->map.map[y][x] != EMPTY)
		counts[2] = 0;
}

int	validate_counts(int p_count, int e_count, int c_count)
{
	if (p_count != 1 || e_count != 1 || c_count < 1)
		return (0);
	return (1);
}

int	count_elements(t_game *game)
{
	int	x;
	int	y;
	int	counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 1;
	game->map.collectible_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			process_cell(game, x, y, counts);
			x++;
		}
		y++;
	}
	if (!validate_counts(counts[0], counts[1], game->map.collectible_count))
		return (0);
	return (counts[2]);
}
