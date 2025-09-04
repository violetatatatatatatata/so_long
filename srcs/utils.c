/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 utils.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: avelandr <avelandr@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/09/03 20:32:16 by avelandr		   #+#	  #+#			  */
/*	 Updated: 2025/09/03 21:49:55 by avelandr		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "solong.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// Libera todos los recursos y sale del juego con un mensaje de error.
void	exit_game(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		if (game->floor.img)
			mlx_destroy_image(game->mlx, game->floor.img);
		if (game->wall.img)
			mlx_destroy_image(game->mlx, game->wall.img);
		if (game->collectible.img)
			mlx_destroy_image(game->mlx, game->collectible.img);
		if (game->player.img)
			mlx_destroy_image(game->mlx, game->player.img);
		if (game->exit_closed.img)
			mlx_destroy_image(game->mlx, game->exit_closed.img);
		if (game->exit_opened.img)
			mlx_destroy_image(game->mlx, game->exit_opened.img);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map.map)
		ft_free_array(game->map.map);
	exit(0);
}

// Maneja el evento de cerrar la ventana. Es una funcion de callback
int	on_destroy(t_game *game)
{
	exit_game(game);
	return (0);
}

char	**append_str_to_array(char **array, char *str)
{
	int		i;
	char	**new_array;

	i = 0;
	if (array == NULL)
	{
		new_array = (char **)ft_calloc(2, sizeof(char *));
		if (!new_array)
			return (NULL);
		new_array[0] = ft_strdup(str);
		return (new_array);
	}
	while (array[i] != NULL)
		i++;
	new_array = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = -1;
	while (array[++i] != NULL)
		new_array[i] = ft_strdup(array[i]);
	new_array[i] = ft_strdup(str);
	ft_free_array(array);
	return (new_array);
}
