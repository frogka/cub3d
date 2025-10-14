/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:24:28 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/14 18:47:22 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//supp ancienne postiion jouer, carre colore qui reste
//gerer deplacemetn horizontaux
//


// void flood_fill(char **cpy, t_map *map, )

void flood_fill(char **cpy_grid, t_map *map, int x, int y)
{
    if (x < 0 || x > map->width || y < 0 || y > map->height)
    {
        printf("Playeur hors cadre\n");
        exit(EXIT_FAILURE);
    }//message d'erreur
    if (cpy_grid[y][x] == ' ' || cpy_grid[y][x] == '\0')
    {
        printf("Map avec un trou\n");
        exit(EXIT_FAILURE);
    }
    if (cpy_grid[y][x] == '1' || cpy_grid[y][x] == 'V')
        return;
    cpy_grid[y][x] = 'V';
    flood_fill(cpy_grid, map, x + 1, y);
    flood_fill(cpy_grid, map, x - 1, y);
    flood_fill(cpy_grid, map, x, y + 1);
    flood_fill(cpy_grid, map, x, y - 1);
}

char **copy_map(char **grid, t_map *map)
{
    int i;
    char **cpy_grid;
    
    i = 0;
    cpy_grid = malloc(sizeof(char *) * (map->height + 1));
    if (!cpy_grid)
        return (NULL);
    while(i < map->height)
    {
        cpy_grid[i] = ft_strdup(grid[i]);
        i++;
    }
    cpy_grid[i] = NULL;
    i = 0;
    while(cpy_grid[i])
    {
        printf("%s\n", cpy_grid[i]);
        printf("%zu\n", ft_strlen(cpy_grid[i++]));
    }
    return (cpy_grid);
}


void draw_map(t_map *map, t_data *data)
{
    int row;
    int col;
    int px;
    int py;
    char c;

    col = 0;
    //if (x < WIDTH && y < HEIGHT)
    //{
        while (col < map->height)
        {
            row = 0;
            while (row < map->width)
            {
                c = map->grid[col][row];
                px = row * TILE;
                py = col * TILE;
                //if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                //    player_position(map, c, row, col);
                draw_square(data, c, px, py);
                row++;
            }
            col++;
        }
        draw_square(data, 'P', map->player_x - TILE / 2, map->player_y - TILE / 2);
        // ajouter un joueur en forme de cercle 
    //}
}


void draw_square(t_data *data, char c, int px, int py)
{
    int tx;
    int ty;

    ty = 0;
    while (ty < TILE)
    {
        tx = 0;
        while (tx < TILE)
        {
            if (c == '1')
                my_mlx_pixel_put(data, tx + px, ty + py , RED);
            else if (c == '0')
                my_mlx_pixel_put(data, tx + px, ty + py, BLUE);
            // else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                // my_mlx_pixel_put(data, tx + px, ty + py, BLACK);
            else if (c == 'P' )//&& tx < RAYON && ty < RAYON)
                my_mlx_pixel_put(data, tx + px, ty + py, GREEN);
            tx++;
        }
        ty++;
    }
}
