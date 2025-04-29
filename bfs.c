/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:46:26 by avelandr          #+#    #+#             */
/*   Updated: 2025/04/29 15:24:47 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*
Comprueba si una posición (x, y) en el mapa es válida para caminar.
	- Que no esté fuera de los límites del mapa.
	- Que no sea una pared (MURO, es decir '1').
*/
int is_valid_position(t_mapa *m, int x, int y)
{
	if (x < 0 || y < 0 || x >= m->filas || y >= m->column)
		return (0);
	if (m->mapa[x][y] == MURO)
		return (0);
	return (1);
}

/*
Libera la memoria que habías reservado para el array visited.
	- Recorre cada fila de visited y libera la memoria de esa fila.
	- Luego libera el propio array de punteros.
*/
void free_visited(int **visited, int filas)
{
	int i;
	i = 0;
	while (i < filas)
		free(visited[i++]);
	free(visited);
}

/*
Crea e inicializa una matriz visited de tamaño [filas][column] a cero.
	- Reserva memoria para el array de punteros.
	- Reserva memoria para cada fila, inicializando cada celda a 0 con calloc.
*/
int **init_visited(int filas, int column)
{
	int **visited;
	int i;

	i = 0;
	visited = malloc(sizeof(int *) * filas);
	if (!visited)
		return (NULL);
	while (i < filas)
	{
		visited[i] = calloc(column, sizeof(int));
		if (!visited[i])
			return (NULL);
		i++;
	}
	return (visited);
}

/*
Busca un camino donde se recojan todos los C (items) y se llegue a la E (salida).
	- Empieza desde (pos_x, pos_y).
	- Añade la posición inicial a la cola queue.
	- Mientras haya posiciones en la cola:
	- Saca una posición c.
	- Si hay un C, disminuye el contador de items.
	- Si se han recogido todos los C y estás en E, devuelve éxito.
	- Para cada dirección posible:
	- Si es una posición válida y no visitada, añádela a la cola y márcala como visitada.
*/
int bfs_algorithm(t_mapa *m, t_pos *queue, int **visited)
{
	int front;
	int back;
	int i;
	t_pos c;
	t_pos moves[4];

	front = 0;
	back = 0;
	queue[back++] = (t_pos){m->pos_x, m->pos_y};
	visited[m->pos_x][m->pos_y] = 1;
	while (front < back)
	{
		c = queue[front++];
		if (m->mapa[c.x][c.y] == 'C')
			m->items--;
		if (m->items == 0 && m->mapa[c.x][c.y] == 'E')
			return (1);
		set_moves(moves, c);
		i = 0;
		while (i < 4)
		{
			if (is_valid_position(m, moves[i].x, moves[i].y)
				&& !visited[moves[i].x][moves[i].y])
			{
				queue[back++] = moves[i];
				visited[moves[i].x][moves[i].y] = 1;
			}
			i++;
		}
	}
	return (0);
}

/*
	- Prepara la matriz visited.
	- Llama al BFS.
	- Libera la memoria de visited al final.
	- Devuelve 1 si hay camino, 0 si no hay.
*/
int shortest_path(t_mapa *m)
{
	t_pos queue[m->filas * m->column];
	int **visited;
	int result;

	visited = init_visited(m->filas, m->column);
	if (!visited)
		return (0);
	result = bfs(m, queue, visited);
	free_visited(visited, m->filas);
	return (result);
}
