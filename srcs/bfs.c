/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 bfs.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/04/29 14:46:26 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 08:25:19 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

char	**copy_map_loop(t_map *map, char **copy)
{
	int	i;

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

char	**copy_map(t_map *map)
{
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	return (copy_map_loop(map, copy));
}

void	process_current_cell(t_bfs *data, char **map_copy, t_pos current)
{
	if (map_copy[current.y][current.x] == ITEM)
	{
		map_copy[current.y][current.x] = EMPTY;
		data->items_to_collect--;
	}
	if (map_copy[current.y][current.x] == EXIT)
		data->found_exit = 1;
}

void	process_queue(t_game *game, t_bfs *data, char **map_copy)
{
	t_pos	current;

	while (data->front < data->back)
	{
		current = data->queue[data->front++];
		process_current_cell(data, map_copy, current);
		enqueue_neighbors(game, data, current);
	}
}

void	enqueue_neighbors(t_game *game, t_bfs *data, t_pos current)
{
	t_pos	new_pos;
	int		dy[4];
	int		dx[4];
	int		i;

	dy[0] = 1;
	dy[1] = -1;
	dy[2] = 0;
	dy[3] = 0;
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = 1;
	dx[3] = -1;
	i = -1;
	while (++i < 4)
	{
		new_pos.y = current.y + dy[i];
		new_pos.x = current.x + dx[i];
		if (is_valid_bfs_position(&game->map, new_pos.y, new_pos.x,
				data->visited))
		{
			data->visited[new_pos.y][new_pos.x] = 1;
			data->queue[data->back++] = new_pos;
		}
	}
}
