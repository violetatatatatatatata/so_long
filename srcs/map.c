/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:06:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/03 23:41:37 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

// Abre y carga el mapa del archivo en la estructura del juego
void	open_map(t_game *game, const char *map_path)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
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
		// Eliminar el carácter de nueva línea si existe
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map.map = append_str_to_array(game->map.map, line);
		game->map.height++;
		free(line);
	}
	close(fd);
	if (game->map.height == 0)
	{
		ft_printf("Error: Mapa vacío.\n");
		exit_game(game);
	}
	game->map.width = ft_strlen(game->map.map[0]);
}

// Verifica que el mapa sea rectangular.
int	check_rectangle(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		if (ft_strlen(game->map.map[i]) != (size_t)game->map.width)
			return (0);
		i++;
	}
	return (1);
}

// Verifica que el mapa esté rodeado de muros.
int check_walls(t_game *game)
{
    int i;
    int width = game->map.width;
    int height = game->map.height;

	// Verificar paredes superior e inferior (filas 0 y height-1)
    i = 0;
    while (i < width)
    {
        if (game->map.map[0][i] != MURO || game->map.map[height - 1][i] != MURO)
            return (0);
        i++;
    }

    // Verificar paredes izquierda y derecha (columnas 0 y width-1)
    i = 0;
    while (i < height)
    {
        if (game->map.map[i][0] != MURO || game->map.map[i][width - 1] != MURO)
            return (0);
        i++;
    }
    return (1);
}

// Cuenta y valida los elementos del mapa (P, E, C).
int	count_elements(t_game *game)
{
	int		x;
	int		y;
	int		p_count;
	int		e_count;

	p_count = 0;
	e_count = 0;
	game->map.collectible_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.map[y][x] == INIT_POINT)
			{
				p_count++;
				game->map.player_pos.x = x;
				game->map.player_pos.y = y;
			}
			else if (game->map.map[y][x] == EXIT)
			{
				e_count++;
				game->map.exit_pos.x = x;
				game->map.exit_pos.y = y;
			}
			else if (game->map.map[y][x] == ITEM)
				game->map.collectible_count++;
			else if (game->map.map[y][x] != MURO && game->map.map[y][x] != EMPTY)
				return (0); // Carácter inválido
			x++;
		}
		y++;
	}
	if (p_count != 1 || e_count != 1 || game->map.collectible_count < 1)
		return (0);
	return (1);
}

// Valida todas las propiedades del mapa.
int	is_valid_map(t_game *game)
{
	if (!check_rectangle(game))
		return (0);
	if (!check_walls(game))
		return (0);
	if (!count_elements(game))
		return (0);
	if (!bfs_path_checker(game))
		return (0);
	return (1);
}
