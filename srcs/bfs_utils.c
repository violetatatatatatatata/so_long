/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 bfs_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/04 09:14:51 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 09:16:58 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

int	is_valid_bfs_position(t_map *map, int x, int y, int **visited)
{
	if (x < 0 || y < 0 || x >= map->height || y >= map->width)
		return (0);
	if (map->map[x][y] == MURO || visited[x][y])
		return (0);
	return (1);
}

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

void	free_bfs_data(t_bfs *data, t_game *game)
{
	if (data->visited)
		free_visited_array(data->visited, game->map.height);
	if (data->queue)
		free(data->queue);
}

void	free_and_return(t_bfs *data, t_game *game, char **map_copy)
{
	free_bfs_data(data, game);
	if (map_copy)
		ft_free_array(map_copy);
}

int	bfs_path_checker(t_game *game)
{
	t_bfs	data;
	char	**map_copy;

	ft_bzero(&data, sizeof(t_bfs));
	map_copy = copy_map(&game->map);
	if (!map_copy)
		return (0);
	if (!init_bfs_data(game, &data, map_copy))
		return (0);
	process_queue(game, &data, map_copy);
	free_and_return(&data, game, map_copy);
	if (data.items_to_collect == 0 && data.found_exit)
		return (1);
	return (0);
}
