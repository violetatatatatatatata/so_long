/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 checker.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/04 09:04:00 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 09:04:55 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

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

int	check_horizontal_walls(t_game *game)
{
	int	i;
	int	width;
	int	height;

	width = game->map.width;
	height = game->map.height;
	i = 0;
	while (i < width)
	{
		if (game->map.map[0][i] != MURO || game->map.map[height - 1][i] != MURO)
			return (0);
		i++;
	}
	return (1);
}

int	check_vertical_walls(t_game *game)
{
	int	i;
	int	width;
	int	height;

	width = game->map.width;
	height = game->map.height;
	i = 0;
	while (i < height)
	{
		if (game->map.map[i][0] != MURO || game->map.map[i][width - 1] != MURO)
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(t_game *game)
{
	if (!check_horizontal_walls(game))
		return (0);
	if (!check_vertical_walls(game))
		return (0);
	return (1);
}

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
