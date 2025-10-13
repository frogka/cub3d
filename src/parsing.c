/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:47:40 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/11 20:19:51 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ordre du parsing map:
// 1. count_map_lines
// 2. fill_map
// 3. player_position
// 4. flood fill

// i = 0;
// if (map.grid[i] < map.width)
// {
//     while( ft_strlen(map.grid[i]) < map.width)
//     {
//         if (map.grid[i][j] == '\0')
//     }
// }

// tant que la ligne existe je la parcours 
// si j (qui parcourt la ligne) est plus petit que la WIDTH
// j a ce moment vaut '\0'
// tant que j est < que width 
// j = ' ';
// j++;
// if j == WIDTH 
// j = '\0';

// boucler jusqua i NULL

char **map_space(t_map *map, char **grid)
{
    int i;
    int j;
    int longueur;
    
   i = 0;
   while (grid[i])
   {
      longueur = ft_strlen(grid[i]);
      j = 0;
      while (grid[i][j])
      {
         if (grid[i][j] == '\0' && longueur < map->width)
         {
            while (j++ < map->width)
               grid[i][j] = ' ';
            grid[i][j] = '\0';
            i++;
            break;
         }
         j++;
      }
   }
   while (map->grid[i])
      printf("Apres traitement %s\n", map->grid[i++]);
   return (map->grid);
}