/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:06:19 by avelandr          #+#    #+#             */
/*   Updated: 2025/04/29 15:19:10 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// Cargar el mapa

/*
   ALGORITMO !! :3
   - Abrir el fichero que contiene el mapa y control de errores
   - Se va contando el número de filas conforme se lee el fichero línea a línea
   - Conforme lee, hace append para anexar la línea leída al array de string mapa
   - Cierra el fichero abierto
 */

void    abrir_mapa(t_mapa *m)
{
	int     fd;
	char    *line;
	char    **aux;

	fd = open(maps/mapa.ber, O_RDONLY);
	if (fd < 0)
		exit(ft_printf("Error.\n"));
	m->filas = 0;
	*aux = NULL;
	while ((line = get_next_line(fd)))
	{
		aux = append_line(m->mapa, line, m->filas);
		if (!aux)
			exit(ft_printf("Error.\n"));
		free(line);
		m->mapa = aux;
		m->filas++;
	}
	close(fd);
	if (m->mapa)
		m->column = ft_strlen(m->mapa[0]);
}

/*
   ALGORITMO !!

   - Hacemos malloc para un array más grande
   - Copiamos lo que ya teníamos
   - Añadimos la nueva línea
   - Liberamos el viejo mapa
   - Devolvemos el nuevo
 */
char    **append_line(char **mapa, char *line, int filas)
{
	char    **nuevo;
	int     i;

	nuevo = malloc(sizeof(char *) * (filas + 2));
	if (!nuevo)
		return (NULL);
	i = 0;
	while (i < filas)
	{
		nuevo[i] = mapa[i];
		i++;
	}
	nuevo[i] = ft_strdup(line);
	nuevo[i + 1] = NULL;
	free(mapa);
	return (nuevo);
}

/*
	- Guardar el mapa en char **mapa
	- Verificar forma rectangular
	- Contar y validar P, E, C
	- Comprobar que está rodeado de muros
	- Validar que hay camino con BFS
*/
int	is_valid_map(t_mapa *m)
{
	char	**mapa;
	int	i;
	int	j;

	mapa = m->mapa;
	if (m->filas != m->column)
		return (1);
	if (check_muros(m) == 1)
		return (1);
	return (0);
}

int	check_muros(t_mapa *m)
{
    int     i;
	int     j;
	char    **mapa;

    i = 0;
	j = 0;
	mapa = m->mapa;
	while (j < m->column)
	{
        if (mapa[0][j] != MURO)
                return (1);
        else
            j++;
    }
	i++;
	while (i < m->filas)
	{
		if (mapa[i][0] != MURO || mapa[i][m->column - 1] != MURO)
			return (1);
		i++;
	}
	j = 0;
    while (j < m->column)
    {
        if (mapa[m->filas - 1][j] != MURO)
            return (1);
        else
            j++;
    }
	return (0);
}

/*
	Comprueba que haya sólo una P y mínimo un E y un C
*/
int	check_PEC(t_mapa *m)
{
	int		    i;
    int		    j;
	int		num_p;
	int		num_e;
	int		num_c;
	char	**mapa;

    i = 0;
	num_p = 0;
	num_e = 0;
	num_c = 0;
	mapa = m->mapa;
	while (++i < m->filas)
	{
		j = 0;
		while (++j < m->column)
        	{
        	        if (mapa[i][j] == INIT_POINT)
				num_p++;
                        else if (mapa[i][j] == EXIT)
				num_e++;
			else if (mapa[i][j] == ITEM)
				num_c++;
        	}
	}
	if (num_p != 1 || num_e != 1 || num_c < 1)
		return (1);
	else
		return (0);
}
