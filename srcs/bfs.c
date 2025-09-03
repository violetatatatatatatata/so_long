/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:46:26 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/03 21:47:48 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

// Comprueba si una posición es válida para el BFS
// 1. Está dentro de los límites del mapa.
// 2. No es una pared ('1').
// 3. No ha sido visitada ya.

int is_valid_bfs_position(t_map *map, int x, int y, int **visited)
{
	if (x < 0 || y < 0 || x >= map->height || y >= map->width)
		return (0);
	if (map->map[x][y] == MURO || visited[x][y])
		return (0);
	return (1);
}

// Libera la memoria del array de visitados.
void	free_visited_array(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

// Realiza una copia profunda del mapa para no modificar el original.
char **copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->map[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}


/*
Busca un camino donde se recojan todos los C (items) y se llegue a la E (salida).
- Crea una copia del mapa para que el BFS no modifique el original.
- Inicializa la cola y el array de visitados.
- Empieza desde la posición inicial del jugador.
- Mientras haya posiciones en la cola:
	- Saca una posición.
	- Si es un coleccionable, lo marca como "recogido" en la copia del mapa y decrementa el contador.
	- Si es la salida y se han recogido todos los coleccionables, devuelve 1 (éxito).
	- Para cada dirección posible, si es una posición válida:
		- La añade a la cola y la marca como visitada.
*/
int bfs_path_checker(t_game *game)
{
	t_pos	*queue;
	int		**visited;
	int		front;
	int		back;
	int		i;
	t_pos	current;
	t_pos	new_pos;
	int		items_to_collect;
	char	**map_copy;
	int		found_exit;

	map_copy = copy_map(&game->map);
	if (!map_copy)
		return (0); // Error de memoria
	items_to_collect = game->map.collectible_count;
	found_exit = 0;

	// Inicializar la cola y el array de visitados
	queue = (t_pos *)malloc(sizeof(t_pos) * (game->map.height * game->map.width));
	if (!queue)
	{
		ft_free_array(map_copy);
		return (0);
	}

	visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (!visited)
	{
		free(queue);
		ft_free_array(map_copy);
		return (0);
	}

	i = 0;
	while (i < game->map.height)
	{
		visited[i] = (int *)ft_calloc(game->map.width, sizeof(int));
		if (!visited[i])
		{
			free_visited_array(visited, i);
			free(queue);
			ft_free_array(map_copy);
			return (0);
		}
		i++;
	}

	front = 0;
	back = 0;

	queue[back++] = game->map.player_pos;
	visited[game->map.player_pos.y][game->map.player_pos.x] = 1;

	while (front < back)
	{
		current = queue[front++];
		if (map_copy[current.y][current.x] == ITEM)
		{
			map_copy[current.y][current.x] = EMPTY;
			items_to_collect--;
		}
		if (map_copy[current.y][current.x] == EXIT)
			found_exit = 1;

		if (items_to_collect == 0 && found_exit)
		{
			free_visited_array(visited, game->map.height);
			free(queue);
			ft_free_array(map_copy);
			return (1); // Éxito
		}

		// Moverse en las 4 direcciones
		new_pos.y = current.y + 1;
		new_pos.x = current.x;
		if (is_valid_bfs_position(&game->map, new_pos.y, new_pos.x, visited))
		{
			visited[new_pos.y][new_pos.x] = 1;
			queue[back++] = new_pos;
		}
		new_pos.y = current.y - 1;
		new_pos.x = current.x;
		if (is_valid_bfs_position(&game->map, new_pos.y, new_pos.x, visited))
		{
			visited[new_pos.y][new_pos.x] = 1;
			queue[back++] = new_pos;
		}
		new_pos.y = current.y;
		new_pos.x = current.x + 1;
		if (is_valid_bfs_position(&game->map, new_pos.y, new_pos.x, visited))
		{
			visited[new_pos.y][new_pos.x] = 1;
			queue[back++] = new_pos;
		}
		new_pos.y = current.y;
		new_pos.x = current.x - 1;
		if (is_valid_bfs_position(&game->map, new_pos.y, new_pos.x, visited))
		{
			visited[new_pos.y][new_pos.x] = 1;
			queue[back++] = new_pos;
		}
	}

	free_visited_array(visited, game->map.height);
	free(queue);
	ft_free_array(map_copy);
	return (0); // No se encontró un camino válido
}
