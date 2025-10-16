/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:43:48 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/16 17:46:39 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_position(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S'
				|| map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				if (map->grid[y][x] == 'N')
					map->player_dir = 3 * PI / 2;
				else if (map->grid[y][x] == 'S')
					map->player_dir = PI / 2;
				else if (map->grid[y][x] == 'E')
					map->player_dir = 0;
				else if (map->grid[y][x] == 'W')
					map->player_dir = PI;
				set_player(map, x, y);
			}
			x++;
		}
		y++;
	}
}

void	is_one_player(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W'))
			map->player_found++;
		i++;
	}
}

int	check_num_player(t_map *map)
{
	if (map->player_found != 1)
	{
		printf("No player or too many\n");
		free_split(map->grid);
		free(map);
		return (1);
	}
	return (0);
}

void	set_player(t_map *map, int x, int y)
{
	map->player_x = x * TILE + TILE / 2; // centre pour la pov
	map->player_y = y * TILE + TILE / 2;
	map->grid[y][x] = '0'; // stocker dans une variable
}
