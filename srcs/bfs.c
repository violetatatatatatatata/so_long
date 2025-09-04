/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:41:16 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/04 02:29:54 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	bfs_path_checker(t_game *game)
{
	t_bfs_data	bfs;
	char		**map_copy;
	int			result;

	if (!init_bfs(game, &bfs, &map_copy))
		return (0);
	if (!init_bfs_visited(game, &bfs))
	{
		ft_free_array(map_copy);
		return (0);
	}
	result = run_bfs(game, &bfs, map_copy);
	free_all_bfs_resources(&bfs, map_copy, game->map.height);
	return (result);
}

int	count_elements(t_game *game)
{
	int	x;
	int	y;

	game->map.player_count = 0;
	game->map.exit_count = 0;
	game->map.collectible_count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (!handle_cell(game, x, y))
				return (0);
		}
	}
	if (game->map.player_count != 1
		|| game->map.exit_count != 1
		|| game->map.collectible_count < 1)
		return (0);
	return (1);
}
