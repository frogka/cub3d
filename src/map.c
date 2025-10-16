/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:24:28 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/16 23:53:44 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	check_map_closed(t_map *map)
{
	char	**cpy_grid;

	cpy_grid = copy_map(map->grid, map);
	if (!cpy_grid)
		return (1);
	if (flood_fill(cpy_grid, map, map->player_x / TILE, map->player_y / TILE))
	{
		free_split(cpy_grid);
		return (1);
	}
	free_split(cpy_grid);
	return (0);
}

int	flood_fill(char **cpy_grid, t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
	{
		printf("Playeur hors cadre\n");
		return (1);
	}
	if (cpy_grid[y][x] == ' ' || cpy_grid[y][x] == '\0')
	{
		printf("Map avec un trou\n");
		return (1);
	}
	if (cpy_grid[y][x] == '1' || cpy_grid[y][x] == 'V')
		return (0);
	cpy_grid[y][x] = 'V';
	if (flood_fill(cpy_grid, map, x + 1, y) == 1)
		return (1);
	if (flood_fill(cpy_grid, map, x - 1, y) == 1)
		return (1);
	if (flood_fill(cpy_grid, map, x, y + 1) == 1)
		return (1);
	if (flood_fill(cpy_grid, map, x, y - 1) == 1)
		return (1);
	return (0);
}

char	**copy_map(char **grid, t_map *map)
{
	int		i;
	char	**cpy_grid;

	i = 0;
	cpy_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!cpy_grid)
		return (NULL);
	while (i < map->height)
	{
		cpy_grid[i] = ft_strdup(grid[i]);
		i++;
	}
	cpy_grid[i] = NULL;
	i = 0;
	printf("voici la copie\n");
	while (cpy_grid[i])
	{
		printf("%s\n", cpy_grid[i]);
		printf("%zu\n", ft_strlen(cpy_grid[i++]));
	}
	return (cpy_grid);
}

void	draw_map(t_map *map, t_data *data)
{
	int		row;
	int		col;
	int		px;
	int		py;
	char	c;

	col = 0;
	while (col < map->height)
	{
		row = 0;
		while (row < map->width)
		{
			c = map->grid[col][row];
			px = row * TILE;
			py = col * TILE;
			draw_square(data, c, px, py);
			row++;
		}
		col++;
	}
	// draw_square(data, 'P', map->player_x - TILE / 2, map->player_y - TILE
		// / 2);
	// ajouter un joueur en forme de cercle
    draw_rays(data);
	draw_player(map, data);
    dist_rays_wall(data);
}

void	draw_square(t_data *data, char c, int px, int py)
{
	int	tx;
	int	ty;

	ty = 0;
	while (ty < TILE)
	{
		tx = 0;
		while (tx < TILE)
		{
			if (c == '1')
				my_mlx_pixel_put(data, tx + px, ty + py, RED);
			else if (c == '0')
				my_mlx_pixel_put(data, tx + px, ty + py, BLUE);
			// else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			// my_mlx_pixel_put(data, tx + px, ty + py, BLACK);
			// else if (c == 'P' )//&& tx < RAYON && ty < RAYON)
			//     my_mlx_pixel_put(data, tx + px, ty + py, GREEN);
			tx++;
		}
		ty++;
	}
}

void	draw_player(t_map *map, t_data *data)
{
	int	x;
	int	y;
	int	cx;
	int	cy;

	y = -TILE_P;
	while (y < TILE_P)
	{
		x = -TILE_P;
		while (x < TILE_P)
		{
			cx = map->player_x + x;
			cy = map->player_y + y;
			if (x * x + y * y <= TILE_P * TILE_P)
				my_mlx_pixel_put(data, cx, cy, GREEN);
			x++;
		}
		y++;
	}
}
