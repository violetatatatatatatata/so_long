/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 bfs_run.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/04 09:17:04 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 09:17:04 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

int	init_visited_loop(t_game *game, int **visited)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		visited[i] = (int *)ft_calloc(game->map.width, sizeof(int));
		if (!visited[i])
		{
			free_visited_array(visited, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	**init_visited(t_game *game)
{
	int	**visited;

	visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (!visited)
		return (NULL);
	if (!init_visited_loop(game, visited))
		return (NULL);
	return (visited);
}

int	init_queue(t_game *game, t_bfs *data)
{
	data->queue = (t_pos *)malloc(sizeof(t_pos)
			* (game->map.height * game->map.width));
	if (!data->queue)
		return (0);
	return (1);
}

int	init_bfs_data(t_game *game, t_bfs *data, char **map_copy)
{
	data->visited = init_visited(game);
	if (!data->visited || !init_queue(game, data))
	{
		free_and_return(data, game, map_copy);
		return (0);
	}
	data->queue[data->back++] = game->map.player_pos;
	data->visited[game->map.player_pos.y][game->map.player_pos.x] = 1;
	data->items_to_collect = game->map.collectible_count;
	data->found_exit = 0;
	return (1);
}
