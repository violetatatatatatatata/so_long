/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:20:30 by avelandr          #+#    #+#             */
/*   Updated: 2025/09/04 09:41:50 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	draw_sprite(t_game *game, t_img sprite, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, sprite.img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	load_sprite(t_game *game, t_img *sprite, char *path)
{
	int	w;
	int	h;

	sprite->img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!sprite->img)
	{
		ft_printf("Error: No se pudo cargar el sprite %s\n", path);
		exit_game(game);
	}
}

void	init_sprites(t_game *game)
{
	load_sprite(game, &game->floor, "./sprites/floor.xpm");
	load_sprite(game, &game->wall, "./sprites/wall.xpm");
	load_sprite(game, &game->collectible, "./sprites/collectible.xpm");
	load_sprite(game, &game->player, "./sprites/player.xpm");
	load_sprite(game, &game->exit_closed, "./sprites/exit_closed.xpm");
	load_sprite(game, &game->exit_opened, "./sprites/exit_opened.xpm");
}
