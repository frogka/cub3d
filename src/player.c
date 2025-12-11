/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:43:48 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/11 00:05:02 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//determine l'orientation du joueur dans la map
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
				set_direction(map, x, y);
				set_virtual_plan(map, x, y);
				set_player(map, x, y);
			}
			x++;
		}
		y++;
	}
}

//compte le nombre de joueurs dasn la map
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

//controle d'un unique joueur
int	check_num_player(t_map *map)
{
	//condition pour aucun joueur + message specifique
	if (map->player_found < 1)
	{
		printf("Error\n");
		printf("No player found\n");
		free_split(map->grid);
		free(map);
		return (1);
	}
	if (map->player_found > 1)
	{
		printf("Too many players\n");
		free_split(map->grid);
		free(map);
		return (1);
	}
	return (0);
}

//positionne dasn la bonne direction la pov du joueur
void	set_direction(t_map *map, int x, int y)
{
	if (map->grid[y][x] == 'N')
	{
		map->dirX = 0;
		map->dirY = -1;
	}
	else if (map->grid[y][x] == 'S')
	{
		map->dirX = 0;
		map->dirY = 1;
	}
	else if (map->grid[y][x] == 'E')
	{
		map->dirX = 1;
		map->dirY = 0;
	}
	else if (map->grid[y][x] == 'W')
	{
		map->dirX = -1;
		map->dirY = 0;
	}
}

//rapport a 90 avec la dir vers ou regarde le joueur
//mur virtuel ou va etre projeter l'image
void set_virtual_plan(t_map *map, int x, int y)
{
	if (map->grid[y][x] == 'N')
	{
		map->planeX = FOV;
		map->planeY = 0;
	}
	else if (map->grid[y][x] == 'S')
	{
		map->planeX = -FOV;
		map->planeY = 0;
	}
	else if (map->grid[y][x] == 'E')
	{
		map->planeX = 0;
		map->planeY = FOV;
	}
	else if (map->grid[y][x] == 'W')
	{
		map->planeX = -FOV;
		map->planeY = 0;
	}
}

void raycast_main(t_data *data)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		data->map->cameraX = 2.0 * x / (double)WIDTH - 1.0;
		init_dda(data->map, &data->ray, data);
		dda_steps(data, &data->ray);
		draw_wall(data, &data->ray, x);
		x++;
	}
}

//centre la pov du P selon sa position dans la map
void	set_player(t_map *map, int x, int y)
{
	map->player_x = x + 0.5; // centre pour la pov
	map->player_y = y + 0.5;
	map->grid[y][x] = '0'; // stocker dans une variable
}
