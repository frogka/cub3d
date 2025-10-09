/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:43:48 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/09 20:35:03 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
//fontion a mettre avant le dessin de la map??
void check_numb_player(t_map *map, char *line, int x, int y)
{
    char c;
    int x;
    int y;

    y = 0;
    while(is_map_line(line))
    {
        while(y < map->height)
        {
            x = 0;
            while(x < map->width)
            {
                if (c == 'N' || c == 'S' || c == 'E' || c == 'W' && map->player_found == 0)
                    map->player_found = 1;
                else if (c == 'N' || c == 'S' || c == 'E' || c == 'W' && map->player_found == 1)
                {
                    //message d'erreur + free si besoin
                   exit (1);
                }
                x++;
            }
            y++;
        }
    }
}*/

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
                map->player_x = x * TILE + TILE / 2; //centre pour la pov
                map->player_y = y * TILE + TILE / 2;
                map->grid[y][x] = '0'; //stocker dans une variable
                 return (0);
                //mettre map->grid[y][x] = '0';
            }
            x++;
        }
        y++;
    }
     return (1);
}

//segfault pour les X,Z etc..
int is_one_player(t_map *map, char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
    
        if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') && map->player_found == 0)
            map->player_found = 1;
        else if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') && map->player_found == 1)
            return (0);
        else if (ft_isalpha_low(line[i]))
            return (0);
        // else if (ft_isalpha_up(line[i]))
        // {
        //     if ((line[i] != 'N' || line[i] != 'S' || line[i] != 'E' || line[i] != 'W'))
        //         return (0);
        // }
        i++;
    }
    return (1);
}


