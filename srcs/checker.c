/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 checker.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/04 01:57:13 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/04 01:57:56 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

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
int	check_walls(t_game *game)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = game->map.width;
	height = game->map.height;
	while (i < width)
	{
		if (game->map.map[0][i] != MURO || game->map.map[height - 1][i] != MURO)
			return (0);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (game->map.map[i][0] != MURO || game->map.map[i][width - 1] != MURO)
			return (0);
		i++;
	}
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
