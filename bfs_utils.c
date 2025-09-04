/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 bfs_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/04 02:00:54 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 02:07:47 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

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

// Abre y carga el mapa del archivo en la estructura del juego
void	open_map(t_game *game, const char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: No se pudo abrir el archivo de mapa.\n");
		exit_game(game);
	}
}

// Carga las líneas del mapa del archivo en la estructura del juego
void	load_map_lines(t_game *game, int fd)
{
	char	*line;
	int		len;

	game->map.height = 0;
	game->map.map = NULL;
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
	close(fd);
	if (game->map.height == 0)
	{
		ft_printf("Error: Mapa vacío.\n");
		exit_game(game);
	}
	game->map.width = ft_strlen(game->map.map[0]);
}
