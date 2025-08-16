/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avelandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:07:03 by avelandr          #+#    #+#             */
/*   Updated: 2025/08/16 17:15:02 by avelandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/*
** get_map_lines_and_length.c
** - Abre el archivo y verifica sus dimensiones
*/
int     get_map_lines_and_length(char *path, int *width)
{
    int     fd;
    char    c;
    int     len;
    int     lines;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    len = 0;
    lines = 0;
    while (read(fd, &c, 1) > 0)
    {
        if (c == '\n')
        {
            if (lines == 0)
                *width = len;
            len = 0;
            lines++;
        }
        else
            len++;
    }
    close(fd);
    if (len > 0)
        lines++;
    return (lines);
}

/*
** check_map_chars.c
** - Valida los carácteres del mapa y determina si el mapa es válido
*/
int     check_map_chars(char **map, int width, int height)
{
    int     i;
    int     j;
    int     p_count;
    int     e_count;
    int     c_count;

    p_count = 0;
    e_count = 0;
    c_count = 0;
    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (map[i][j] == 'P')
                p_count++;
            else if (map[i][j] == 'E')
                e_count++;
            else if (map[i][j] == 'C')
                c_count++;
            else if (map[i][j] != '0' && map[i][j] != '1')
                return (0);
            j++;
        }
        i++;
    }
    return (p_count == 1 && e_count == 1 && c_count >= 1);
}

/*
** check_map_walls.c
** - Verifica si el programa está totalmente rodeado por muros
*/
int     check_map_walls(char **map, int width, int height)
{
    int     i;
    int     j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                if (map[i][j] != '1')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

void    free_map(char **map, int height)
{
    int i;

    i = 0;
    while (i < height)
        free(map[i++]);
    free(map);
}

/*
** parse_map.c
** - Verifica totalmente si el mapa es válido
*/
char    **parse_map(char *path, int *width, int *height)
{
    int     fd;
    char    **map;
    int     i;

    *height = get_map_lines_and_length(path, width);
    if (*height <= 0 || *width <= 0)
        return (NULL);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    map = (char **)malloc(sizeof(char *) * (*height));
    if (!map)
        return (NULL);
    i = 0;
    while (i < *height)
    {
        map[i] = get_next_line(fd);
        if (!map[i] || (int)ft_strlen(map[i]) - (map[i][ft_strlen(map[i]) - 1] == '\n') != *width)
        {
            free_map(map, i);
            close(fd);
            return (NULL);
        }
        i++;
    }
    close(fd);
    if (!check_map_chars(map, *width, *height) || !check_map_walls(map, *width, *height))
    {
        free_map(map, *height);
        return (NULL);
    }
    return (map);
}
