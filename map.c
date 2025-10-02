/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:24:28 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/02 19:18:11 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_map(t_map *map, t_data *data, int x, int y)
{
    printf("draw_map called\n");
    int col_x;
    int col_y;
    int px;
    int py;
    char c;

    col_y = 0;
    if (x < LARGEUR && y < HAUTEUR)
    {
        while (col_y < map->height)
        {
            col_x = 0;
            while (col_x < map->width)
            {
                c = map->grid[col_y][col_x];
                px = col_x * TILE;
                py = col_y * TILE;
                draw_square(data, c, px, py);
                col_x++;
            }
            col_y++;
        }
    }
}


void draw_square(t_data *data, char c, int x, int y)
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
                my_mlx_pixel_put(data, tx + x, ty + y , RED);
            else if (c == '0')
                my_mlx_pixel_put(data, tx + x, ty + y, BLUE);
            else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                my_mlx_pixel_put(data, tx + x, ty + y, BLACK);
            tx++;
        }
        ty++;
    }
}
