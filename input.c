/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:25:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/04/29 15:49:06 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/*
- Pulsas una tecla.
- MiniLibX llama automáticamente a tu función handle_key(int keycode, t_game *g).
- En handle_key:
    Llamas a set_moves para calcular a dónde podrías moverte desde tu posición actual.
Según el keycode (W, A, S, D), eliges el movimiento correcto (moves[0], moves[1], etc).

- ¿Es válida esa nueva posición? (is_valid_position)
    No puede ser muro.
    No puede salirse del mapa.
    Debe contener los itemps y caracteres necesarios

- Si es válida:
    Actualizas la posición del jugador.
    Sumas 1 a su contador de movimientos.

- Redibujas el mapa (render_game(g)).
- Si pulsas ESC:
    Llamas a exit_game(g), que cierra la ventana y libera memoria.
	
	KEYCODE es el número que representa la tecla que pulsas. Lo recibe
	automáticamente tu función de eventos (key_hook) de MiniLibX.

	Pulsas W → keycode será 'W' (en ASCII, 87).
	Pulsas ESC → keycode será 65307.
	MiniLibX te pasa keycode como primer argumento en la función para capturar teclas.
*/

// Genera las 4 posibles posiciones a donde te puedes mover desde la posición actual.
void set_moves(t_pos moves[4], t_pos c)
{
    moves[0] = (t_pos){c.x - 1, c.y};
    moves[1] = (t_pos){c.x + 1, c.y};
    moves[2] = (t_pos){c.x, c.y - 1};
    moves[3] = (t_pos){c.x, c.y + 1};
}

int handle_key(int keycode, t_game *g)
{
    t_pos moves[4];
    t_pos actual;
    t_pos next;

    actual.x = g->mapa.pos_x;
    actual.y = g->mapa.pos_y;
    set_moves(moves, actual);
    if (!set_next_move(keycode, moves, &next, g))
        return (0);
    if (is_valid_position(&g->mapa, next.x, next.y))
    {
        g->mapa.pos_x = next.x;
        g->mapa.pos_y = next.y;
        g->pj.movimientos++;
        ft_printf("Movimientos: %d\n", g->pj.movimientos);
        render_game(g);
    }
    return (0);
}

int set_next_move(int keycode, t_pos moves[4], t_pos *next, t_game *g)
{
    if (keycode == ARRIBA)
        *next = moves[0];
    else if (keycode == ABAJO)
        *next = moves[1];
    else if (keycode == IZQ)
        *next = moves[2];
    else if (keycode == DER)
        *next = moves[3];
    else if (keycode == ESC)
        exit_game(g);
    else
        return (0);
    return (1);
}
