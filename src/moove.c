/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdutille <jdutille@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:13:10 by jdutille          #+#    #+#             */
/*   Updated: 2025/10/08 02:47:13 by jdutille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void moove_v(int keycode, t_data *data)
{
	double next_x;
	double next_y;
	int grid_x;
	int grid_y;
	printf("adresse data = %p\n", data);
	printf("adresse map  = %p\n", data->map);

	if (keycode == KEY_UP)
	{
		next_x = data->map->player_x + cos(data->map->player_dir) * speed;
		next_y = data->map->player_y + sin(data->map->player_dir) * speed;
	}
	else
	{
		next_x = data->map->player_x - cos(data->map->player_dir) * speed;
		next_y = data->map->player_y - sin(data->map->player_dir) * speed;
	}
	grid_x = (int)(next_x / TILE);
	grid_y = (int)(next_y / TILE);

	printf("grid_x = %d, grid_y = %d, height = %d, width = %d\n", grid_x, grid_y, data->map->height, data->map->width);
	//gere la distance aux murs
	if (data->map->grid[grid_y][grid_x] != '1')
	{
		data->map->player_x = next_x;
		data->map->player_y = next_y;
		draw_map(data->map, data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	}

}
/*
void moove_h(int keycode, t_map *map, t_data *data)
{
	double next_x;
	double next_y;
	int grid_x;
	int grid_y;

	if (keycode == KEY_LEFT)
	{
		next_x = map->player_x - cos(map->player_dir) * speed;
		next_y = map->player_y - sin(map->player_dir) * speed;
	}
	grid_x = (int)next_x / TILE;
	grid_y = (int)next_y / TILE;

	if (map->grid[grid_y][grid_x] != 1)
	{
		map->player_x = next_x;
		map->player_y = next_y;
		draw_map(map, data, map->player_x, map->player_y);
	}
}
*/