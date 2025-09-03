/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:47:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/08/16 18:18:20 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

#include <mlx.h>
#include <stdio.h> // Para printf
#include <stdlib.h> // Para exit()

// Define los códigos de teclas para los movimientos
#define KEY_ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define EVENT_DESTROY_NOTIFY 17

// Define los códigos de eventos de MLX
#define EVENT_KEY_PRESS 2
#define EVENT_KEY_RELEASE 3
#define EVENT_MOUSE_PRESS 4
#define EVENT_MOUSE_RELEASE 5
#define EVENT_MOUSE_MOVE 6
#define EVENT_DESTROY_NOTIFY 17

#define TILE_SIZE 64

// Estructura para gestionar un sprite (imagen)
typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

// Estructura principal para almacenar el estado del juego
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	collectible;
	t_img	exit;
	char	**map;
	int		player_x;
	int		player_y;
	int		collect_count;
	int		moves;
	int		map_width;
	int		map_height;
}	t_game;

