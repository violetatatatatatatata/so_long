/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:13:51 by avelandr          #+#    #+#             */
/*   Updated: 2025/04/29 17:16:23 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Dibujar en pantalla lo que se ha cargado en el mapa (char **mapa), usando
	MiniLibX (mlx_put_image_to_window).

	- Recorrer el mapa fila a fila y columna a columna.
	- Según el carácter ('0', '1', 'C', 'E', 'P') dibujar:
		suelo (img_ground)
		pared (img_wall)
		item (img_item)
		salida (img_exit)
		jugador (img_player) → en la posición del jugador, no de P en el mapa.
	- Loop doble (for filas y columnas).
	- Para cada (i, j):
		Primero dibujar siempre el suelo (img_ground).
		Luego si el mapa tiene:
			'1' → dibujar pared (img_wall).
			'C' → dibujar item (img_item).
			'E' → dibujar salida (img_exit).
			'P' → no dibujar nada especial (porque ahora el jugador real se pinta aparte).
	- Dibujar jugador en g->pj.x y g->pj.y.
*/

