/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:43:48 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/10 19:39:55 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int player_position(t_map *map)
{
    int x;
    int y;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' || map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
            {
                if (map->grid[y][x] == 'N')
                    map->player_dir = 3 * PI / 2;       
                else if (map->grid[y][x] == 'S')
                    map->player_dir = PI / 2;
                else if (map->grid[y][x] == 'E')
                    map->player_dir = 0;
                else if (map->grid[y][x] == 'W')
                    map->player_dir = PI;
                    //conditon si player dir != - 1 appel 
                    //focniton et 3 lignes en desuus
                    //gain de place
                map->player_x = x * TILE + TILE / 2; //centre pour la pov
                map->player_y = y * TILE + TILE / 2;
                map->grid[y][x] = '0'; //stocker dans une variable
                return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}


void is_one_player(t_map *map, char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
    
        if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
            map->player_found++;
        i++;
    }
}



