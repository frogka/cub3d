/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:24:28 by jdutille          #+#    #+#             */
/*   Updated: 2025/12/10 22:35:31 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//check la que la map est bien bornee
int	check_map_closed(t_map *map)
{
	char	**cpy_grid;

	cpy_grid = copy_map(map->grid, map);
	if (!cpy_grid)
		return (1);
	if (flood_fill(cpy_grid, map, map->player_x, map->player_y))
	{
		free_split(cpy_grid);
		return (1);
	}
	free_split(cpy_grid);
	return (0);
}

//check que la map est correcte
//pas de trou, pas de joueur a la limite ou hors cadre
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
	//message d'erreur
}

//copy la map pour le flood fill
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

//dessin de la map en 2d
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
			px = round(row * TILE * data->m->scale);
			py = round(col * TILE * data->m->scale);
			draw_square(data, c, px, py);
			row++;
		}
		col++;
	}
	draw_player(map, data);
}

//dessin de la map en 2d
void	draw_square(t_data *data, char c, int px, int py)
{
	int	tx;
	int	ty;
	int size;

	ty = 0;
	size = round(TILE * data->m->scale);
	while (ty < size)
	{
		tx = 0;
		while (tx < size)
		{
			if (c == '1')
				my_mlx_pixel_put(&data->img, tx + px , ty + py , RED);
			else if (c == '0')
				my_mlx_pixel_put(&data->img, tx + px , ty + py , BLUE);
			tx++;
		}
		ty++;
	}
}

//dessin du joueur dans la map 2d
void	draw_player(t_map *map, t_data *data)
{
	int	x;
	int	y;
	int	cx;
	int	cy;
	int radius;

	radius = TILE_P * data->m->scale;
	y = -radius;
	while (y < radius)
	{
		x = -radius;
		while (x < radius)
		{
			cx = map->player_x * data->m->scale + x;
			cy = map->player_y * data->m->scale + y;
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(&data->img, cx , cy , GREEN);
			x++;
		}
		y++;
	}
}
