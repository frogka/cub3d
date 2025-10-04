/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:24:28 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/03 23:47:32 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_map(t_map *map, t_data *data, int x, int y)
{
    int row;
    int col;
    int px;
    int py;
    char c;

    col = 0;
    if (x < LARGEUR && y < HAUTEUR)
    {
        while (col < map->height)
        {
            row = 0;
            while (row < map->width)
            {
                c = map->grid[col][row];
                px = row * TILE;
                py = col * TILE;
                if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                    player_position(map, c, row, col);
                draw_square(data, c, px, py);
                row++;
            }
            col++;
        }
    }
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
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                my_mlx_pixel_put(data, tx + px, ty + py, BLACK);
            tx++;
        }
        ty++;
    }
}
